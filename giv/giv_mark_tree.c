/* 
 * Copyright (c) 2000 by Dov Grobgeld <dov@imagic.weizmann.ac.il>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.
 */

#include <gtk/gtk.h>
#include "giv_types.h"

GtkWidget *w_tree_view;
GHashTable *hash_giv_path_to_iter = NULL;

static void get_iter_from_mark_set(mark_set_t *mark_set,
				   GtkTreeStore *model,
				   /* output */
				   GtkTreeIter **iter);

static void get_iter_from_string_path(const char *filename,
				      const char *string_path,
				      GtkTreeStore *model,
				      /* output */
				      GtkTreeIter **iter);
static void strip_last_leaf(const char *string_path,
			    /* output */
			    char **string_path_no_last_leaf,
			    char **string_last_leaf);

static void
cb_toggled (GtkCellRendererToggle *cell,
	    gchar                 *path_string,
	    gpointer               data)
{
  GtkTreeModel *model = GTK_TREE_MODEL (data);
  GtkTreeIter iter;
  GtkTreePath *path = gtk_tree_path_new_from_string (path_string);
  gboolean value;
  int i;

  gtk_tree_model_get_iter (model, &iter, path);
  gtk_tree_model_get (model, &iter, 0, &value, -1);

  value = !value;
  gtk_tree_store_set (GTK_TREE_STORE (model), &iter, 0, value, -1);
  
#if 0
  if (value)
      gtk_tree_view_expand_row(GTK_TREE_VIEW(w_tree_view), path, FALSE);
  else
      gtk_tree_view_collapse_row(GTK_TREE_VIEW(w_tree_view), path);
#endif
      
  gtk_tree_path_free (path);

  /* Loop over all the mark sets and make them visible or invisible */
  for(i=0; i<mark_set_list->len; i++)
    {
      mark_set_t *mark_set = g_ptr_array_index (mark_set_list, i);

      /* Here check if there is a match between the path string and the
	 dataset name... If we are opening up a node with subnodes, then
	 we should loop over the subnotes and set up the visible datasets.
      */
      if (strstr(mark_set->tree_path_string, path_string) == mark_set->tree_path_string && (
          mark_set->tree_path_string[strlen(path_string)] == '\0'
          || mark_set->tree_path_string[strlen(path_string)] == ':'))
	{
	  mark_set->is_visible = value;
	}
      
    }
  
  gtk_image_viewer_redraw(GTK_WIDGET(image_viewer));
}

GtkWidget *create_giv_mark_tree(GPtrArray *mark_set_list)
{
  int i;
  GtkWidget *w_tree_window;
  GtkWidget *vbox, *tree_view, *scrolled_window;
  GtkTreeStore *model;
  GtkTreeViewColumn *column;
  GtkCellRenderer *cell;
  gchar *str;
  GSList *parent_array;
  GtkTreeIter iter;
  gchar *last_filename = NULL;

  w_tree_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size (GTK_WINDOW (w_tree_window), 400, 350);
  vbox = gtk_vbox_new (FALSE, 8);
  gtk_container_add(GTK_CONTAINER(w_tree_window), vbox);
  scrolled_window = gtk_scrolled_window_new (NULL, NULL);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
				  GTK_POLICY_AUTOMATIC,
				  GTK_POLICY_AUTOMATIC);
  gtk_box_pack_start (GTK_BOX (vbox), scrolled_window, TRUE, TRUE, 0);
  
  model = gtk_tree_store_new (3, G_TYPE_BOOLEAN, G_TYPE_STRING, G_TYPE_INT);
  w_tree_view = tree_view = gtk_tree_view_new_with_model (GTK_TREE_MODEL (model));
  gtk_container_add (GTK_CONTAINER (scrolled_window), tree_view);
  
  /* Toggle column */
  column = gtk_tree_view_column_new();
  cell = gtk_cell_renderer_toggle_new ();
  g_signal_connect (cell, "toggled",
		    G_CALLBACK (cb_toggled), model);
  gtk_tree_view_column_pack_start (column, cell, TRUE);
  gtk_tree_view_column_set_attributes (column, cell,
				       "active", 0,
				       NULL);
  gtk_tree_view_column_set_resizable(column, TRUE);
  gtk_tree_view_column_set_min_width(column, 70);
  gtk_tree_view_column_set_title (column, "Visible");
  gtk_tree_view_append_column (GTK_TREE_VIEW (tree_view), column);
  
  /* First text column */
  column = gtk_tree_view_column_new();
  cell = gtk_cell_renderer_text_new ();
  gtk_tree_view_column_set_resizable(column, TRUE);
  gtk_tree_view_column_set_min_width(column, 150);
  gtk_tree_view_column_pack_start (column, cell, TRUE);
  gtk_tree_view_column_set_attributes (column, cell,
				       "text", 1,
				       NULL);
  gtk_tree_view_column_set_title (column, "Path");
  gtk_tree_view_append_column (GTK_TREE_VIEW (tree_view), column);

  /* Second column */
  column = gtk_tree_view_column_new();
  gtk_tree_view_column_set_resizable(column, TRUE);
  cell = gtk_cell_renderer_text_new ();
  g_object_set (G_OBJECT (cell),
		"xalign", 1.0,
		NULL);
  gtk_tree_view_column_pack_start (column, cell, TRUE);
  gtk_tree_view_column_set_fixed_width (column, 50);
  gtk_tree_view_column_set_attributes (column, cell,
				       "text", 2,
				       NULL);
  gtk_tree_view_column_set_title (column, "#nodes");
  gtk_tree_view_append_column (GTK_TREE_VIEW (tree_view), column);

  /* Make a stack for poping back parents when building the tree */
  parent_array = NULL;

  /* Create the hash table that maps between giv paths and the
     iters of the tree.
  */
  if (hash_giv_path_to_iter)
      g_hash_table_destroy(hash_giv_path_to_iter);
  hash_giv_path_to_iter = g_hash_table_new_full(g_str_hash,
						g_str_equal,
						g_free,
						NULL);
  
  for(i=0; i<mark_set_list->len; i++)
    {
      mark_set_t *mark_set = g_ptr_array_index (mark_set_list, i);
      GtkTreePath *tree_path;
      GtkTreeIter *iter;
      char num_points_string[20];

      get_iter_from_mark_set(mark_set, model,
                             &iter);

#if 0
      /* Is there really anything I need to do with the iterator... */
      if (!parent_array || strcmp(last_filename, mark_set->file_name) != 0)
	{
	  GtkTreeIter *iter = g_new0(GtkTreeIter, 1);
	  while(parent_array)
	    {
	      g_free(parent_array->data);
	      parent_array = parent_array->next;
	    }

	  gtk_tree_store_append (model, iter, NULL);
	  
	  gtk_tree_store_set (model, iter,
			      0, mark_set->is_visible,
			      1, mark_set->file_name,
			      -1);
	  
	  last_filename = mark_set->file_name;
	  parent_array = g_slist_prepend(parent_array, iter);
	}

      /* Here we should really split the path_name into its tree components
	 and compare if it is in the tree. For the moment, lets just
	 store the whole path. */
      iter = g_new0(GtkTreeIter, 1);

      sprintf(num_points_string, "%d", mark_set->points->len);
      gtk_tree_store_append(model, iter, (GtkTreeIter*)(parent_array->data));
      gtk_tree_store_set(model, iter,
			 0, TRUE,
			 1, mark_set->path_name,
			 2, mark_set->points->len,
			 -1);
#endif
      
      tree_path = gtk_tree_model_get_path(GTK_TREE_MODEL(model), iter);
      if (mark_set->tree_path_string)
	g_free(mark_set->tree_path_string);
      mark_set->tree_path_string = gtk_tree_path_to_string(tree_path);
      gtk_tree_path_free(tree_path);
      /* g_free(&iter); */

    }
  gtk_tree_view_expand_all(GTK_TREE_VIEW(tree_view));

  gtk_widget_show_all(vbox);

  return w_tree_window;
}

/*======================================================================
//  Given a mark set, extract the corresponding iter that belongs to
//  it. This is jupst a front end to the recursive
//  get_iter_from_string_path().
//----------------------------------------------------------------------
*/
static void get_iter_from_mark_set(mark_set_t *mark_set,
				   GtkTreeStore *model,
				   /* output */
				   GtkTreeIter **iter)
{
    get_iter_from_string_path(mark_set->file_name,
			      mark_set->path_name,
			      model,
			      iter);
}

/*======================================================================
//  Returns an iterator from the hash table. If it doesn't exist,
//  then a new key is created.
//----------------------------------------------------------------------
*/
static void get_iter_from_string_path(const char *filename,
				      const char *string_path,
				      GtkTreeStore *model,
				      /* output */
				      GtkTreeIter **iter)
{
    gchar *string_path_no_last_leaf;
    gchar *string_last_leaf;
    GtkTreeIter *parent, *new_iter;
    gchar *key;
    
    if (string_path == NULL)
      key = g_strdup_printf("%s", filename);
    else
      key = g_strdup_printf("%s///%s", filename, string_path);

    *iter = (GtkTreeIter*)g_hash_table_lookup(hash_giv_path_to_iter, key);
    
    if (*iter)
      {
	g_free(key);
        return;
      }

    if (string_path)
      {
	strip_last_leaf(string_path,
			// output
			&string_path_no_last_leaf,
			&string_last_leaf);

	get_iter_from_string_path(filename,
				  string_path_no_last_leaf,
				  model,
				  // output 
				  &parent);
      }
    else
      {
        string_last_leaf = g_strdup(filename);
	parent = NULL;
      }
    
    new_iter = g_new0(GtkTreeIter, 1);
    gtk_tree_store_append(model, new_iter, parent);
    gtk_tree_store_set (model, new_iter,
			0, 1,
			1, string_last_leaf,
			2, 0,
			-1);

    g_hash_table_insert(hash_giv_path_to_iter,
			(gpointer)(key),
			(gpointer)(new_iter));
    *iter = new_iter;
}

static void strip_last_leaf(const char *string_path,
			    /* output */
			    char **string_path_no_last_leaf,
			    char **string_last_leaf)
{
  gchar *split_pos;
  
  split_pos = g_strrstr(string_path, "/");

  if (split_pos)
    {
      *string_last_leaf = g_strdup(split_pos+1);
      *string_path_no_last_leaf = g_strndup(string_path, split_pos - string_path);
    }
  else
    {
      *string_path_no_last_leaf = NULL;
      *string_last_leaf = g_strdup(string_path);
    }
}