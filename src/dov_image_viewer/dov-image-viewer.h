/* Generated by GOB (v2.0.12)   (do not edit directly) */

#include <glib.h>
#include <glib-object.h>


#include <stdlib.h>
#include <gtk/gtk.h>

#ifndef __DOV_IMAGE_VIEWER_H__
#define __DOV_IMAGE_VIEWER_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/*
 * Type checking and casting macros
 */
#define DOV_TYPE_IMAGE_VIEWER	(dov_image_viewer_get_type())
#define DOV_IMAGE_VIEWER(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), dov_image_viewer_get_type(), DovImageViewer)
#define DOV_IMAGE_VIEWER_CONST(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), dov_image_viewer_get_type(), DovImageViewer const)
#define DOV_IMAGE_VIEWER_CLASS(klass)	G_TYPE_CHECK_CLASS_CAST((klass), dov_image_viewer_get_type(), DovImageViewerClass)
#define DOV_IS_IMAGE_VIEWER(obj)	G_TYPE_CHECK_INSTANCE_TYPE((obj), dov_image_viewer_get_type ())

#define DOV_IMAGE_VIEWER_GET_CLASS(obj)	G_TYPE_INSTANCE_GET_CLASS((obj), dov_image_viewer_get_type(), DovImageViewerClass)

/* Private structure type */
typedef struct _DovImageViewerPrivate DovImageViewerPrivate;

/*
 * Main object structure
 */
#ifndef __TYPEDEF_DOV_IMAGE_VIEWER__
#define __TYPEDEF_DOV_IMAGE_VIEWER__
typedef struct _DovImageViewer DovImageViewer;
#endif
struct _DovImageViewer {
	GtkWidget __parent__;
	/*< private >*/
	DovImageViewerPrivate *_priv;
};

/*
 * Class definition
 */
typedef struct _DovImageViewerClass DovImageViewerClass;
struct _DovImageViewerClass {
	GtkWidgetClass __parent__;
	/*signal*/void (* set_scroll_adjustments) (DovImageViewer * self, GtkAdjustment * hadjustment, GtkAdjustment * vadjustment);
	/*signal*/void (* image_annotate) (DovImageViewer * self, GdkPixbuf * pixbuf, gint shift_x, gint shift_y, gdouble scale_x, gdouble scale_y);
	/*signal*/void (* flip_changed) (DovImageViewer * self, gboolean horizontal_flip, gboolean vertical_flip);
};


/*
 * Public methods
 */
GType	dov_image_viewer_get_type	(void);
GtkWidget * 	dov_image_viewer_new	(GdkPixbuf * pixbuf);
GtkWidget * 	dov_image_viewer_new_from_file	(const gchar * filename);
void 	dov_image_viewer_expose_area	(DovImageViewer * self,
					int exp_x0,
					int exp_y0,
					int w,
					int h);
void 	dov_image_viewer_set_freeze	(DovImageViewer * self,
					gboolean is_frozen);
gint 	dov_image_viewer_redraw	(DovImageViewer * self,
					gboolean clear_cache);
gint 	dov_image_viewer_zoom_around_fixed_point	(DovImageViewer * self,
					double new_scale_x,
					double new_scale_y,
					double old_x,
					double old_y,
					double new_x,
					double new_y);
gint 	dov_image_viewer_zoom_to_box	(DovImageViewer * self,
					double world_min_x,
					double world_min_y,
					double world_max_x,
					double world_max_y,
					double pixel_margin,
					gboolean preserve_aspect);
void 	dov_image_viewer_set_hadjustment	(DovImageViewer * self,
					GtkAdjustment * adjustment);
void 	dov_image_viewer_set_vadjustment	(DovImageViewer * self,
					GtkAdjustment * adjustment);
void 	dov_image_viewer_set_image	(DovImageViewer * self,
					GdkPixbuf * image);
const GdkPixbuf * 	dov_image_viewer_get_image	(DovImageViewer * self);
void 	dov_image_viewer_set_scroll_adjustments	(DovImageViewer * self,
					GtkAdjustment * hadjustment,
					GtkAdjustment * vadjustment);
void 	dov_image_viewer_image_annotate	(DovImageViewer * self,
					GdkPixbuf * pixbuf,
					gint shift_x,
					gint shift_y,
					gdouble scale_x,
					gdouble scale_y);
void 	dov_image_viewer_flip_changed	(DovImageViewer * self,
					gboolean horizontal_flip,
					gboolean vertical_flip);
guint 	dov_image_viewer_get_image_width	(DovImageViewer * self);
guint 	dov_image_viewer_get_image_height	(DovImageViewer * self);
void 	dov_image_viewer_canv_coord_to_img_coord	(DovImageViewer * self,
					double cx,
					double cy,
					double * imgx,
					double * imgy);
void 	dov_image_viewer_img_coord_to_canv_coord	(DovImageViewer * self,
					double imgx,
					double imgy,
					double * canvx,
					double * canvy);
void 	dov_image_viewer_set_zoom_range	(DovImageViewer * self,
					double min_zoom,
					double max_zoom);
void 	dov_image_viewer_get_scale_and_shift	(DovImageViewer * self,
					gdouble * scale_x,
					gdouble * scale_y,
					gint * shift_x,
					gint * shift_y);
void 	dov_image_viewer_set_transfer_map	(DovImageViewer * self,
					guint8 * rmap,
					guint8 * gmap,
					guint8 * bmap);
void 	dov_image_viewer_set_fill_on_resize	(DovImageViewer * self,
					bool whether);
void 	dov_image_viewer_one_shot_block_fill_on_resize	(DovImageViewer * self);
gboolean 	dov_image_viewer_get_fill_on_resize	(DovImageViewer * self);
void 	dov_image_viewer_set_scroll_region	(DovImageViewer * self,
					double x0,
					double y0,
					double x1,
					double y1);
void 	dov_image_viewer_set_flip	(DovImageViewer * self,
					gboolean do_flip_horizontal,
					gboolean do_flip_vertical);
void 	dov_image_viewer_zoom_reset	(DovImageViewer * self);

/*
 * Signal connection wrapper macros
 */
#if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#define dov_image_viewer_connect__set_scroll_adjustments(object,func,data)	g_signal_connect(DOV_IMAGE_VIEWER(__extension__ ({DovImageViewer *___object = (object); ___object; })),"set_scroll_adjustments",(GCallback) __extension__ ({void (* ___set_scroll_adjustments) (DovImageViewer * ___fake___self, GtkAdjustment * ___fake___hadjustment, GtkAdjustment * ___fake___vadjustment, gpointer ___data ) = (func); ___set_scroll_adjustments; }), (data))
#define dov_image_viewer_connect_after__set_scroll_adjustments(object,func,data)	g_signal_connect_after(DOV_IMAGE_VIEWER(__extension__ ({DovImageViewer *___object = (object); ___object; })),"set_scroll_adjustments",(GCallback) __extension__ ({void (* ___set_scroll_adjustments) (DovImageViewer * ___fake___self, GtkAdjustment * ___fake___hadjustment, GtkAdjustment * ___fake___vadjustment, gpointer ___data ) = (func); ___set_scroll_adjustments; }), (data))
#define dov_image_viewer_connect_data__set_scroll_adjustments(object,func,data,destroy_data,flags)	g_signal_connect_data(DOV_IMAGE_VIEWER(__extension__ ({DovImageViewer *___object = (object); ___object; })),"set_scroll_adjustments",(GCallback) __extension__ ({void (* ___set_scroll_adjustments) (DovImageViewer * ___fake___self, GtkAdjustment * ___fake___hadjustment, GtkAdjustment * ___fake___vadjustment, gpointer ___data ) = (func); ___set_scroll_adjustments; }), (data), (destroy_data), (GConnectFlags)(flags))
#define dov_image_viewer_connect__image_annotate(object,func,data)	g_signal_connect(DOV_IMAGE_VIEWER(__extension__ ({DovImageViewer *___object = (object); ___object; })),"image_annotate",(GCallback) __extension__ ({void (* ___image_annotate) (DovImageViewer * ___fake___self, GdkPixbuf * ___fake___pixbuf, gint ___fake___shift_x, gint ___fake___shift_y, gdouble ___fake___scale_x, gdouble ___fake___scale_y, gpointer ___data ) = (func); ___image_annotate; }), (data))
#define dov_image_viewer_connect_after__image_annotate(object,func,data)	g_signal_connect_after(DOV_IMAGE_VIEWER(__extension__ ({DovImageViewer *___object = (object); ___object; })),"image_annotate",(GCallback) __extension__ ({void (* ___image_annotate) (DovImageViewer * ___fake___self, GdkPixbuf * ___fake___pixbuf, gint ___fake___shift_x, gint ___fake___shift_y, gdouble ___fake___scale_x, gdouble ___fake___scale_y, gpointer ___data ) = (func); ___image_annotate; }), (data))
#define dov_image_viewer_connect_data__image_annotate(object,func,data,destroy_data,flags)	g_signal_connect_data(DOV_IMAGE_VIEWER(__extension__ ({DovImageViewer *___object = (object); ___object; })),"image_annotate",(GCallback) __extension__ ({void (* ___image_annotate) (DovImageViewer * ___fake___self, GdkPixbuf * ___fake___pixbuf, gint ___fake___shift_x, gint ___fake___shift_y, gdouble ___fake___scale_x, gdouble ___fake___scale_y, gpointer ___data ) = (func); ___image_annotate; }), (data), (destroy_data), (GConnectFlags)(flags))
#define dov_image_viewer_connect__flip_changed(object,func,data)	g_signal_connect(DOV_IMAGE_VIEWER(__extension__ ({DovImageViewer *___object = (object); ___object; })),"flip_changed",(GCallback) __extension__ ({void (* ___flip_changed) (DovImageViewer * ___fake___self, gboolean ___fake___horizontal_flip, gboolean ___fake___vertical_flip, gpointer ___data ) = (func); ___flip_changed; }), (data))
#define dov_image_viewer_connect_after__flip_changed(object,func,data)	g_signal_connect_after(DOV_IMAGE_VIEWER(__extension__ ({DovImageViewer *___object = (object); ___object; })),"flip_changed",(GCallback) __extension__ ({void (* ___flip_changed) (DovImageViewer * ___fake___self, gboolean ___fake___horizontal_flip, gboolean ___fake___vertical_flip, gpointer ___data ) = (func); ___flip_changed; }), (data))
#define dov_image_viewer_connect_data__flip_changed(object,func,data,destroy_data,flags)	g_signal_connect_data(DOV_IMAGE_VIEWER(__extension__ ({DovImageViewer *___object = (object); ___object; })),"flip_changed",(GCallback) __extension__ ({void (* ___flip_changed) (DovImageViewer * ___fake___self, gboolean ___fake___horizontal_flip, gboolean ___fake___vertical_flip, gpointer ___data ) = (func); ___flip_changed; }), (data), (destroy_data), (GConnectFlags)(flags))
#else /* __GNUC__ && !__STRICT_ANSI__ */
#define dov_image_viewer_connect__set_scroll_adjustments(object,func,data)	g_signal_connect(DOV_IMAGE_VIEWER(object),"set_scroll_adjustments",(GCallback)(func),(data))
#define dov_image_viewer_connect_after__set_scroll_adjustments(object,func,data)	g_signal_connect_after(DOV_IMAGE_VIEWER(object),"set_scroll_adjustments",(GCallback)(func),(data))
#define dov_image_viewer_connect_data__set_scroll_adjustments(object,func,data,destroy_data,flags)	g_signal_connect_data(DOV_IMAGE_VIEWER(object),"set_scroll_adjustments",(GCallback)(func),(data),(destroy_data),(GConnectFlags)(flags))
#define dov_image_viewer_connect__image_annotate(object,func,data)	g_signal_connect(DOV_IMAGE_VIEWER(object),"image_annotate",(GCallback)(func),(data))
#define dov_image_viewer_connect_after__image_annotate(object,func,data)	g_signal_connect_after(DOV_IMAGE_VIEWER(object),"image_annotate",(GCallback)(func),(data))
#define dov_image_viewer_connect_data__image_annotate(object,func,data,destroy_data,flags)	g_signal_connect_data(DOV_IMAGE_VIEWER(object),"image_annotate",(GCallback)(func),(data),(destroy_data),(GConnectFlags)(flags))
#define dov_image_viewer_connect__flip_changed(object,func,data)	g_signal_connect(DOV_IMAGE_VIEWER(object),"flip_changed",(GCallback)(func),(data))
#define dov_image_viewer_connect_after__flip_changed(object,func,data)	g_signal_connect_after(DOV_IMAGE_VIEWER(object),"flip_changed",(GCallback)(func),(data))
#define dov_image_viewer_connect_data__flip_changed(object,func,data,destroy_data,flags)	g_signal_connect_data(DOV_IMAGE_VIEWER(object),"flip_changed",(GCallback)(func),(data),(destroy_data),(GConnectFlags)(flags))
#endif /* __GNUC__ && !__STRICT_ANSI__ */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif