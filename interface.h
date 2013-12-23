#ifndef __INTERFACE_H
#define __INTERFACE_H

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

G_BEGIN_DECLS

void update_statusbar(GtkTextBuffer *buffer, GtkStatusbar *statusbar);
void mark_set_callback(GtkTextBuffer *buffer, const GtkTextIter *new_location, GtkTextMark *mark, gpointer data);
GdkPixbuf *create_pixbuf(const gchar *filename);
void show_about(GtkWidget *widget, gpointer data);
void undo_redo(GtkWidget *widget, gpointer item);

G_END_DECLS

#endif
