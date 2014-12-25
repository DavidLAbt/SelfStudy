#include <gst/gst.h>
#include <stdio.h>

//Initialize gstreamer with Commandline options
int main(int argc, char* argv[]) {
  
  gboolean silent = FALSE;
  gchar *savefile = NULL;
  
  GOptionContext *ctx;
  
  GError* err = NULL;
  
  GOptionEntry entries[] = {
    { "silent", 's', 0, G_OPTION_ARG_NONE, &silent, "do not output status information", NULL}, 
    { "output", 'o', 0, G_OPTION_ARG_STRING, &savefile, "save xml representation of pipeline to FILE and exit", "FILE" },
    { NULL }
  };
  
  // Creates a new option context.  
  // GOptionContext *g_option_context_new (const gchar *parameter_string);
  // parameter_string : a string which is displayed in the first line of --help output
  ctx = g_option_context_new("- You application");
  
  
  //void g_option_context_add_main_entries (
  //       GOptionContext *context, const GOptionEntry *entries, const gchar *translation_domain);
  //A convenience function which creates a main group if it doesn't exist, 
  // adds the entries to it and sets the translation domain
  g_option_context_add_main_entries(ctx, entries, NULL);
  
  //Adds a GOptionGroup to the context , so that parsing with context will recognize the options in the group.  
  g_option_context_add_group (ctx, gst_init_get_option_group ());
  
  if (!g_option_context_parse (ctx, &argc, &argv, &err)) {
    g_print ("Failed to initialize: %s\n", err->message);
    g_error_free (err);
    return 1;
  }
  
  printf ("Run me with --help to see the Application options appended.\n");
  return 0;
}