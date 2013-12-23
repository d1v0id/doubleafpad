#include "interface.h"

void update_statusbar(GtkTextBuffer *buffer, GtkStatusbar *statusbar);
void mark_set_callback(GtkTextBuffer *buffer, const GtkTextIter *new_location, GtkTextMark *mark, gpointer data);
GdkPixbuf *create_pixbuf(const gchar *filename);
void show_about(GtkWidget *widget, gpointer data);
void undo_redo(GtkWidget *widget, gpointer item);

void update_statusbar(GtkTextBuffer *buffer,
    GtkStatusbar *statusbar)
{
    gchar *msg;
    gint row, col;
    GtkTextIter iter;

    gtk_statusbar_pop(statusbar, 0);

    gtk_text_buffer_get_iter_at_mark(buffer,
        &iter, gtk_text_buffer_get_insert(buffer));

    row = gtk_text_iter_get_line(&iter);
    col = gtk_text_iter_get_line_offset(&iter);

    msg = g_strdup_printf("%d : %d", col+1, row+1);

    gtk_statusbar_push(statusbar, 0, msg);

    g_free(msg);
}

void mark_set_callback(GtkTextBuffer *buffer,
    const GtkTextIter *new_location, GtkTextMark *mark,
    gpointer data)
{
    update_statusbar(buffer, GTK_STATUSBAR(data));
}

GdkPixbuf *create_pixbuf(const gchar *filename)
{
    GdkPixbuf *pixbuf;
    GError *error = NULL;
    pixbuf = gdk_pixbuf_new_from_file(filename, &error);
    if (!pixbuf) {
        fprintf(stderr, "%s\n", error->message);
        g_error_free(error);
    }

    return pixbuf;
}

void show_about(GtkWidget *widget, gpointer data)
{
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("doubleafpad.png", NULL);

    GtkWidget *dialog = gtk_about_dialog_new();
    gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(dialog), "Doubleafpad");
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), "0.1");
    gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog), "(c) Dmitry Konnov");
    gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog),
        "Doubleafpad - simple text editor.");
    gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog),
        "http://www.dmitrykonnov.wordpress.com");
    gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), pixbuf);
    g_object_unref(pixbuf), pixbuf = NULL;
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void undo_redo(GtkWidget *widget, gpointer item)
{
    static int count = 2;
    const char *name = gtk_widget_get_name(widget);

    if (strcmp(name, "undo")) {
        count++;
    }
    else {
        count--;
    }

    if (count < 0) {
        gtk_widget_set_sensitive(widget, FALSE);
        gtk_widget_set_sensitive(item, TRUE);
    }

    if (count > 5) {
        gtk_widget_set_sensitive(widget, FALSE);
        gtk_widget_set_sensitive(item, TRUE);
    }
}
