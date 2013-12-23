#include "interface.h"
#include "settings.h"
#include "texttools.h"

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *vbox;

    GtkWidget *menubar;
    GtkWidget *mg_filemenu; /* menu group for file operations */
    GtkWidget *mg_file;
    GtkWidget *mn_new;
    GtkWidget *mn_open;
    GtkWidget *mn_save;
    GtkWidget *mn_saveas;
    GtkWidget *mn_sep1;
    GtkWidget *mn_quit;
    GtkWidget *mg_editmenu; /* menu group for text operations */
    GtkWidget *mg_edit;
    GtkWidget *mn_undo;
    GtkWidget *mn_redo;
    GtkWidget *mn_sep2;
    GtkWidget *mn_copy;
    GtkWidget *mn_paste;
    GtkWidget *mn_cut;
    GtkWidget *mn_sep3;
    GtkWidget *mn_find;
    GtkWidget *mn_replace;
    GtkWidget *mg_settingsmenu; /* menu group for settings */
    GtkWidget *mg_settings;
    GtkWidget *mn_options;
    GtkWidget *mg_helpmenu; /* menu group for help */
    GtkWidget *mg_help;
    GtkWidget *mn_about;
    GtkAccelGroup *accel_group = NULL;

    GtkWidget *toolbar;
    GtkToolItem *btn_new;
    GtkToolItem *btn_open;
    GtkToolItem *btn_save;
    GtkToolItem *btn_sep1;
    GtkToolItem *btn_undo;
    GtkToolItem *btn_redo;
    GtkToolItem *btn_sep2;
    GtkToolItem *btn_copy;
    GtkToolItem *btn_paste;
    GtkToolItem *btn_cut;
    GtkToolItem *btn_sep3;

    GtkWidget *txt_view;
    GtkWidget *statusbar;

    GtkTextBuffer *text_buffer;

    gtk_init(&argc, &argv);

    /* main window */
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_NONE);
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 400);
    gtk_window_set_title(GTK_WINDOW(window), "Unsaved - doubleafpad");
    gtk_window_set_icon(GTK_WINDOW(window), create_pixbuf("doubleafpad.png"));

    vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    /* menu */
    accel_group = gtk_accel_group_new();
    gtk_window_add_accel_group(GTK_WINDOW(window), accel_group);
    menubar = gtk_menu_bar_new();

    mg_filemenu = gtk_menu_new();
    mg_file = gtk_menu_item_new_with_mnemonic("_File");
    mn_new = gtk_image_menu_item_new_from_stock(GTK_STOCK_NEW, accel_group);
    mn_open = gtk_image_menu_item_new_from_stock(GTK_STOCK_OPEN, accel_group);
    mn_save = gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE, accel_group);
    mn_saveas = gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE_AS, NULL /*accel_group*/);
    mn_sep1 = gtk_separator_menu_item_new();
    mn_quit = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT, accel_group);

    mg_editmenu = gtk_menu_new();
    mg_edit = gtk_menu_item_new_with_mnemonic("_Edit");
    mn_undo = gtk_image_menu_item_new_from_stock(GTK_STOCK_UNDO, NULL /*accel_group*/);
    mn_redo = gtk_image_menu_item_new_from_stock(GTK_STOCK_REDO, NULL /*accel_group*/);
    mn_sep2 = gtk_separator_menu_item_new();
    mn_copy = gtk_image_menu_item_new_from_stock(GTK_STOCK_COPY, accel_group);
    mn_paste = gtk_image_menu_item_new_from_stock(GTK_STOCK_PASTE, accel_group);
    mn_cut = gtk_image_menu_item_new_from_stock(GTK_STOCK_CUT, accel_group);
    mn_sep3 = gtk_separator_menu_item_new();
    mn_find = gtk_image_menu_item_new_from_stock(GTK_STOCK_FIND, accel_group);
    mn_replace = gtk_image_menu_item_new_from_stock(GTK_STOCK_FIND_AND_REPLACE, accel_group); 

    mg_settingsmenu = gtk_menu_new();
    mg_settings = gtk_menu_item_new_with_mnemonic("_Settings");
    mn_options = gtk_image_menu_item_new_from_stock(GTK_STOCK_PROPERTIES, NULL /*accel_group*/);

    mg_helpmenu = gtk_menu_new();
    mg_help = gtk_menu_item_new_with_mnemonic("_Help");
    mn_about = gtk_image_menu_item_new_from_stock(GTK_STOCK_ABOUT, NULL);

    gtk_widget_add_accelerator(mn_new, "activate", accel_group, GDK_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator(mn_open, "activate", accel_group, GDK_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator(mn_save, "activate", accel_group, GDK_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    /*gtk_widget_add_accelerator(mn_saveas, "activate", accel_group, GDK_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);*/
    gtk_widget_add_accelerator(mn_quit, "activate", accel_group, GDK_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    /*gtk_widget_add_accelerator(mn_undo, "activate", accel_group, GDK_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator(mn_redo, "activate", accel_group, GDK_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);*/
    gtk_widget_add_accelerator(mn_copy, "activate", accel_group, GDK_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator(mn_paste, "activate", accel_group, GDK_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator(mn_cut, "activate", accel_group, GDK_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator(mn_find, "activate", accel_group, GDK_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator(mn_replace, "activate", accel_group, GDK_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    /*gtk_widget_add_accelerator(mn_options, "activate", accel_group, GDK_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);*/

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(mg_file), mg_filemenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(mg_filemenu), mn_new);
    gtk_menu_shell_append(GTK_MENU_SHELL(mg_filemenu), mn_open);
    gtk_menu_shell_append(GTK_MENU_SHELL(mg_filemenu), mn_save);
    gtk_menu_shell_append(GTK_MENU_SHELL(mg_filemenu), mn_saveas);
    gtk_menu_shell_append(GTK_MENU_SHELL(mg_filemenu), mn_sep1);
    gtk_menu_shell_append(GTK_MENU_SHELL(mg_filemenu), mn_quit);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), mg_file);

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(mg_edit), mg_editmenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(mg_editmenu), mn_undo);
    gtk_menu_shell_append(GTK_MENU_SHELL(mg_editmenu), mn_redo);
    gtk_menu_shell_append(GTK_MENU_SHELL(mg_editmenu), mn_sep2);
    gtk_menu_shell_append(GTK_MENU_SHELL(mg_editmenu), mn_copy);
    gtk_menu_shell_append(GTK_MENU_SHELL(mg_editmenu), mn_paste);
    gtk_menu_shell_append(GTK_MENU_SHELL(mg_editmenu), mn_cut);
    gtk_menu_shell_append(GTK_MENU_SHELL(mg_editmenu), mn_sep3);
    gtk_menu_shell_append(GTK_MENU_SHELL(mg_editmenu), mn_find);
    gtk_menu_shell_append(GTK_MENU_SHELL(mg_editmenu), mn_replace);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), mg_edit);

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(mg_settings), mg_settingsmenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(mg_settingsmenu), mn_options);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), mg_settings);

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(mg_help), mg_helpmenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(mg_helpmenu), mn_about);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), mg_help);

    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 3);
    
    /* toolbar */
    toolbar = gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);

    btn_new = gtk_tool_button_new_from_stock(GTK_STOCK_NEW);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), btn_new, -1);

    btn_open = gtk_tool_button_new_from_stock(GTK_STOCK_OPEN);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), btn_open, -1);

    btn_save = gtk_tool_button_new_from_stock(GTK_STOCK_SAVE);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), btn_save, -1);

    btn_sep1 = gtk_separator_tool_item_new();
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), btn_sep1, -1);

    btn_undo= gtk_tool_button_new_from_stock(GTK_STOCK_UNDO);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), btn_undo, -1);

    btn_redo = gtk_tool_button_new_from_stock(GTK_STOCK_REDO);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), btn_redo, -1);

    btn_sep2 = gtk_separator_tool_item_new();
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), btn_sep2, -1);

    btn_copy = gtk_tool_button_new_from_stock(GTK_STOCK_COPY);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), btn_copy, -1);

    btn_paste = gtk_tool_button_new_from_stock(GTK_STOCK_PASTE);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), btn_paste, -1);

    btn_cut = gtk_tool_button_new_from_stock(GTK_STOCK_CUT);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), btn_cut, -1);

    btn_sep3 = gtk_separator_tool_item_new();
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), btn_sep3, -1);

    gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 5);


    /* text field */
    txt_view = gtk_text_view_new();
    gtk_box_pack_start(GTK_BOX(vbox), txt_view, TRUE, TRUE, 0);
    gtk_widget_grab_focus(txt_view);

    text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(txt_view));

    /* statusbar */
    statusbar = gtk_statusbar_new();
    gtk_box_pack_start(GTK_BOX(vbox), statusbar, FALSE, FALSE, 0);


    /* menu buttons signals */
    g_signal_connect(G_OBJECT(mn_options), "activate",
        G_CALLBACK(show_settings), NULL);
    g_signal_connect(G_OBJECT(mn_about), "activate",
        G_CALLBACK(show_about), NULL);
    g_signal_connect(G_OBJECT(mn_quit), "activate",
        G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(mn_new), "activate",
        G_CALLBACK(new_file), NULL);

    /* toolbar buttons signals */
    g_signal_connect(G_OBJECT(btn_new), "clicked",
        G_CALLBACK(new_file), NULL);
    g_signal_connect(G_OBJECT(btn_undo), "clicked",
        G_CALLBACK(undo_redo), btn_redo);
    g_signal_connect(G_OBJECT(btn_redo), "clicked",
        G_CALLBACK(undo_redo), btn_undo);

    /* update line and col numbers */
    g_signal_connect(text_buffer, "changed",
        G_CALLBACK(update_statusbar), statusbar);
    g_signal_connect_object(text_buffer, "mark_set",
        G_CALLBACK(mark_set_callback), statusbar, 0);
    update_statusbar(text_buffer, GTK_STATUSBAR(statusbar));

    /* main window signals */
    g_signal_connect_swapped(G_OBJECT(window), "destroy",
        G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
