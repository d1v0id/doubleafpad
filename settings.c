#include "settings.h"

void show_settings(GtkWidget *widget, gpointer data);

void close_window(GtkWidget *widget, gpointer window)
{
        gtk_widget_destroy(GTK_WIDGET(window));
}

void show_settings(GtkWidget *widget, gpointer data)
{
    GtkWidget *settings;
    GtkWidget *btn_append;
    GtkWidget *btn_cancel;
    GtkWidget *vbox;
    GtkWidget *hbox;
    GtkWidget *halign;
    GtkWidget *valign;

    settings = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(settings), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(settings), 450, 300);
    gtk_window_set_title(GTK_WINDOW(settings), "Settings - doubleafpad");
    gtk_container_set_border_width(GTK_CONTAINER(settings), 10);

    vbox = gtk_vbox_new(FALSE, 5);

    valign = gtk_alignment_new(0, 1, 0, 0);
    gtk_container_add(GTK_CONTAINER(vbox), valign);
    gtk_container_add(GTK_CONTAINER(settings), vbox);

    hbox = gtk_hbox_new(TRUE, 3);

    btn_append = gtk_button_new_with_label("Append");
    gtk_widget_set_size_request(btn_append, 70, 30);
    gtk_container_add(GTK_CONTAINER(hbox), btn_append);
    btn_cancel= gtk_button_new_with_label("Cancel");
    gtk_container_add(GTK_CONTAINER(hbox), btn_cancel);

    halign = gtk_alignment_new(1, 0, 0, 0);
    gtk_container_add(GTK_CONTAINER(halign), hbox);

    gtk_box_pack_start(GTK_BOX(vbox), halign, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(btn_cancel), "clicked",
        G_CALLBACK(close_window), G_OBJECT(settings));

    g_signal_connect_swapped(G_OBJECT(settings), "destroy",
        G_CALLBACK(close_window), G_OBJECT(settings));

    gtk_window_set_modal(GTK_WINDOW(settings), TRUE);
    gtk_widget_show_all(settings);
}
