// GUI calculator project

#include <gtk-3.0/gtk/gtk.h>
#include "misc_strings.h"
#include "tinyexpr/tinyexpr.c"

typedef struct {
  /**
  * Contains all buttons and lebel except the 'equals' button
  */
  GtkLabel* w_lbl_display;
  GtkLabel* w_lbl_msg;
  GtkWidget* w_btn_1;
  GtkWidget* w_btn_2;
  GtkWidget* w_btn_3;
  GtkWidget* w_btn_4;
  GtkWidget* w_btn_5;
  GtkWidget* w_btn_6;
  GtkWidget* w_btn_7;
  GtkWidget* w_btn_8;
  GtkWidget* w_btn_9;
  GtkWidget* w_btn_0;
  GtkWidget* w_btn_dot;
  GtkWidget* w_btn_add;
  GtkWidget* w_btn_minus;
  GtkWidget* w_btn_x;
  GtkWidget* w_btn_div;
  GtkWidget* w_btn_ac;
} app_widgets;

int main(int argc, char* argv[]) {
  GtkBuilder* builder;
  GtkWidget* window;
  app_widgets* widgets = g_slice_new(app_widgets);
  gtk_init(&argc, &argv);
  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "glade/window_main.glade", NULL);
  window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
  // get pointers to display label and radio buttons
  widgets->w_lbl_display = GTK_LABEL(gtk_builder_get_object(builder, "lbl_display"));
  widgets->w_lbl_msg = GTK_LABEL(gtk_builder_get_object(builder, "lbl_msg"));
  widgets->w_btn_1 = GTK_WIDGET(gtk_builder_get_object(builder, "btn_1"));
  widgets->w_btn_2 = GTK_WIDGET(gtk_builder_get_object(builder, "btn_2"));
  widgets->w_btn_3 = GTK_WIDGET(gtk_builder_get_object(builder, "btn_3"));
  widgets->w_btn_4 = GTK_WIDGET(gtk_builder_get_object(builder, "btn_4"));
  widgets->w_btn_5 = GTK_WIDGET(gtk_builder_get_object(builder, "btn_5"));
  widgets->w_btn_6 = GTK_WIDGET(gtk_builder_get_object(builder, "btn_6"));
  widgets->w_btn_7 = GTK_WIDGET(gtk_builder_get_object(builder, "btn_7"));
  widgets->w_btn_8 = GTK_WIDGET(gtk_builder_get_object(builder, "btn_8"));
  widgets->w_btn_9 = GTK_WIDGET(gtk_builder_get_object(builder, "btn_9"));
  widgets->w_btn_0 = GTK_WIDGET(gtk_builder_get_object(builder, "btn_0"));
  widgets->w_btn_dot = GTK_WIDGET(gtk_builder_get_object(builder, "btn_dot"));
  widgets->w_btn_add = GTK_WIDGET(gtk_builder_get_object(builder, "btn_add"));
  widgets->w_btn_minus = GTK_WIDGET(gtk_builder_get_object(builder, "btn_minus"));
  widgets->w_btn_x = GTK_WIDGET(gtk_builder_get_object(builder, "btn_x"));
  widgets->w_btn_div = GTK_WIDGET(gtk_builder_get_object(builder, "btn_div"));
  widgets->w_btn_ac = GTK_WIDGET(gtk_builder_get_object(builder, "btn_ac"));
  // connect all the widgets and display window
  gtk_builder_connect_signals(builder, widgets);
  g_object_unref(builder);
  gtk_window_set_title(GTK_WINDOW(window), "calc");
  gtk_widget_show_all(window);
  gtk_main();
  // free memory used by widget struct
  g_slice_free(app_widgets, widgets);
  return 0;
}

void on_window_main_destroy() {
  /**
  * Called when program is closed by user, closes program
  */
  gtk_main_quit();
}

void on_btn_equals_clicked(GtkButton* button, app_widgets* widgets) {
  /**
  * When equals button is clicked, this function calculates the expression
  * entered in the label
  * @param button the equals button that is clicked
  * @param widgets struct that contains all buttons (except equals) and
  * the label
  */
  int err;
  char ans_str[21];
  double ans = te_interp(gtk_label_get_text(widgets->w_lbl_display), &err);
  if ((err != 0)||(isnan(ans))) {
    gtk_label_set_text(widgets->w_lbl_msg, "Syntax Error");
  }
  else {
    snprintf(ans_str,21,"Ans=%lf",ans);
    gtk_label_set_text(widgets->w_lbl_msg, ans_str);
  }
  gtk_label_set_text(widgets->w_lbl_display, "0");
}

void on_btn_ac_clicked(GtkButton* button, app_widgets* widgets) {
  gtk_label_set_text(widgets->w_lbl_display, "0");
}

void on_btn_1_clicked(GtkButton* button, app_widgets* widgets) {
  char* lbl_txt = (char*)gtk_label_get_text(widgets->w_lbl_display);
  if (strcmp(lbl_txt,"0") == 0) {
    gtk_label_set_text(widgets->w_lbl_display, "1");
  }
  else {
    unsigned int txt_len = strlen(lbl_txt);
    if (txt_len+1 >= gtk_label_get_max_width_chars(widgets->w_lbl_display)) {
      gtk_label_set_max_width_chars(widgets->w_lbl_display, strlen(lbl_txt)+1);
    }
    str_cat(lbl_txt, "1");
    gtk_label_set_text(widgets->w_lbl_display, lbl_txt);
  }
}

void on_btn_2_clicked(GtkButton* button, app_widgets* widgets) {
  char* lbl_txt = (char*)gtk_label_get_text(widgets->w_lbl_display);
  if (strcmp(lbl_txt,"0") == 0) {
    gtk_label_set_text(widgets->w_lbl_display, "2");
  }
  else {
    unsigned int txt_len = strlen(lbl_txt);
    if (txt_len+1 >= gtk_label_get_max_width_chars(widgets->w_lbl_display)) {
      gtk_label_set_max_width_chars(widgets->w_lbl_display, strlen(lbl_txt)+1);
    }
    str_cat(lbl_txt, "2");
    gtk_label_set_text(widgets->w_lbl_display, lbl_txt);
  }
}

void on_btn_3_clicked(GtkButton* button, app_widgets* widgets) {
  char* lbl_txt = (char*)gtk_label_get_text(widgets->w_lbl_display);
  if (strcmp(lbl_txt,"0") == 0) {
    gtk_label_set_text(widgets->w_lbl_display, "3");
  }
  else {
    unsigned int txt_len = strlen(lbl_txt);
    if (txt_len+1 >= gtk_label_get_max_width_chars(widgets->w_lbl_display)) {
      gtk_label_set_max_width_chars(widgets->w_lbl_display, strlen(lbl_txt)+1);
    }
    str_cat(lbl_txt, "3");
    gtk_label_set_text(widgets->w_lbl_display, lbl_txt);
  }
}

void on_btn_4_clicked(GtkButton* button, app_widgets* widgets) {
  char* lbl_txt = (char*)gtk_label_get_text(widgets->w_lbl_display);
  if (strcmp(lbl_txt,"0") == 0) {
    gtk_label_set_text(widgets->w_lbl_display, "4");
  }
  else {
    unsigned int txt_len = strlen(lbl_txt);
    if (txt_len+1 >= gtk_label_get_max_width_chars(widgets->w_lbl_display)) {
      gtk_label_set_max_width_chars(widgets->w_lbl_display, strlen(lbl_txt)+1);
    }
    str_cat(lbl_txt, "4");
    gtk_label_set_text(widgets->w_lbl_display, lbl_txt);
  }
}

void on_btn_5_clicked(GtkButton* button, app_widgets* widgets) {
  char* lbl_txt = (char*)gtk_label_get_text(widgets->w_lbl_display);
  if (strcmp(lbl_txt,"0") == 0) {
    gtk_label_set_text(widgets->w_lbl_display, "5");
  }
  else {
    unsigned int txt_len = strlen(lbl_txt);
    if (txt_len+1 >= gtk_label_get_max_width_chars(widgets->w_lbl_display)) {
      gtk_label_set_max_width_chars(widgets->w_lbl_display, strlen(lbl_txt)+1);
    }
    str_cat(lbl_txt, "5");
    gtk_label_set_text(widgets->w_lbl_display, lbl_txt);
  }
}

void on_btn_6_clicked(GtkButton* button, app_widgets* widgets) {
  char* lbl_txt = (char*)gtk_label_get_text(widgets->w_lbl_display);
  if (strcmp(lbl_txt,"0") == 0) {
    gtk_label_set_text(widgets->w_lbl_display, "6");
  }
  else {
    unsigned int txt_len = strlen(lbl_txt);
    if (txt_len+1 >= gtk_label_get_max_width_chars(widgets->w_lbl_display)) {
      gtk_label_set_max_width_chars(widgets->w_lbl_display, strlen(lbl_txt)+1);
    }
    str_cat(lbl_txt, "6");
    gtk_label_set_text(widgets->w_lbl_display, lbl_txt);
  }
}

void on_btn_7_clicked(GtkButton* button, app_widgets* widgets) {
  char* lbl_txt = (char*)gtk_label_get_text(widgets->w_lbl_display);
  if (strcmp(lbl_txt,"0") == 0) {
    gtk_label_set_text(widgets->w_lbl_display, "7");
  }
  else {
    unsigned int txt_len = strlen(lbl_txt);
    if (txt_len+1 >= gtk_label_get_max_width_chars(widgets->w_lbl_display)) {
      gtk_label_set_max_width_chars(widgets->w_lbl_display, strlen(lbl_txt)+1);
    }
    str_cat(lbl_txt, "7");
    gtk_label_set_text(widgets->w_lbl_display, lbl_txt);
  }
}

void on_btn_8_clicked(GtkButton* button, app_widgets* widgets) {
  char* lbl_txt = (char*)gtk_label_get_text(widgets->w_lbl_display);
  if (strcmp(lbl_txt,"0") == 0) {
    gtk_label_set_text(widgets->w_lbl_display, "8");
  }
  else {
    unsigned int txt_len = strlen(lbl_txt);
    if (txt_len+1 >= gtk_label_get_max_width_chars(widgets->w_lbl_display)) {
      gtk_label_set_max_width_chars(widgets->w_lbl_display, strlen(lbl_txt)+1);
    }
    str_cat(lbl_txt, "8");
    gtk_label_set_text(widgets->w_lbl_display, lbl_txt);
  }
}

void on_btn_9_clicked(GtkButton* button, app_widgets* widgets) {
  char* lbl_txt = (char*)gtk_label_get_text(widgets->w_lbl_display);
  if (strcmp(lbl_txt,"0") == 0) {
    gtk_label_set_text(widgets->w_lbl_display, "9");
  }
  else {
    unsigned int txt_len = strlen(lbl_txt);
    if (txt_len+1 >= gtk_label_get_max_width_chars(widgets->w_lbl_display)) {
      gtk_label_set_max_width_chars(widgets->w_lbl_display, strlen(lbl_txt)+1);
    }
    str_cat(lbl_txt, "9");
    gtk_label_set_text(widgets->w_lbl_display, lbl_txt);
  }
}

void on_btn_0_clicked(GtkButton* button, app_widgets* widgets) {
  char* lbl_txt = (char*)gtk_label_get_text(widgets->w_lbl_display);
  if (strcmp(lbl_txt,"0") == 0) {
    // doNothing
  }
  else {
    unsigned int txt_len = strlen(lbl_txt);
    if (txt_len+1 >= gtk_label_get_max_width_chars(widgets->w_lbl_display)) {
      gtk_label_set_max_width_chars(widgets->w_lbl_display, strlen(lbl_txt)+1);
    }
    str_cat(lbl_txt, "0");
    gtk_label_set_text(widgets->w_lbl_display, lbl_txt);
  }
}

void on_btn_add_clicked(GtkButton* button, app_widgets* widgets) {
  char* lbl_txt = (char*)gtk_label_get_text(widgets->w_lbl_display);
  unsigned int txt_len = strlen(lbl_txt);
  if (txt_len+1 >= gtk_label_get_max_width_chars(widgets->w_lbl_display)) {
    gtk_label_set_max_width_chars(widgets->w_lbl_display, strlen(lbl_txt)+1);
  }
  str_cat(lbl_txt, "+");
  gtk_label_set_text(widgets->w_lbl_display, lbl_txt);
}

void on_btn_minus_clicked(GtkButton* button, app_widgets* widgets) {
  char* lbl_txt = (char*)gtk_label_get_text(widgets->w_lbl_display);
  unsigned int txt_len = strlen(lbl_txt);
  if (txt_len+1 >= gtk_label_get_max_width_chars(widgets->w_lbl_display)) {
    gtk_label_set_max_width_chars(widgets->w_lbl_display, strlen(lbl_txt)+1);
  }
  str_cat(lbl_txt, "-");
  gtk_label_set_text(widgets->w_lbl_display, lbl_txt);
}

void on_btn_x_clicked(GtkButton* button, app_widgets* widgets) {
  char* lbl_txt = (char*)gtk_label_get_text(widgets->w_lbl_display);
  unsigned int txt_len = strlen(lbl_txt);
  if (txt_len+1 >= gtk_label_get_max_width_chars(widgets->w_lbl_display)) {
    gtk_label_set_max_width_chars(widgets->w_lbl_display, strlen(lbl_txt)+1);
  }
  str_cat(lbl_txt, "*");
  gtk_label_set_text(widgets->w_lbl_display, lbl_txt);
}

void on_btn_div_clicked(GtkButton* button, app_widgets* widgets) {
  char* lbl_txt = (char*)gtk_label_get_text(widgets->w_lbl_display);
  unsigned int txt_len = strlen(lbl_txt);
  if (txt_len+1 >= gtk_label_get_max_width_chars(widgets->w_lbl_display)) {
    gtk_label_set_max_width_chars(widgets->w_lbl_display, strlen(lbl_txt)+1);
  }
  str_cat(lbl_txt, "/");
  gtk_label_set_text(widgets->w_lbl_display, lbl_txt);
}

void on_btn_dot_clicked(GtkButton* button, app_widgets* widgets) {
  char* lbl_txt = (char*)gtk_label_get_text(widgets->w_lbl_display);
  unsigned int txt_len = strlen(lbl_txt);
  if (txt_len+1 >= gtk_label_get_max_width_chars(widgets->w_lbl_display)) {
    gtk_label_set_max_width_chars(widgets->w_lbl_display, strlen(lbl_txt)+1);
  }
  str_cat(lbl_txt, ".");
  gtk_label_set_text(widgets->w_lbl_display, lbl_txt);
}
