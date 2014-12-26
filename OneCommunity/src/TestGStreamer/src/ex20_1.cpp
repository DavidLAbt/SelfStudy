#include <gst/gst.h>


/* message handle function */
static gboolean my_bus_callback(GstBus *bus, GstMessage * msg, gpointer data) {
  
  // get the main loop
  GMainLoop *loop = (GMainLoop* ) data;
  
  // handle message 
  switch (GST_MESSAGE_TYPE (msg) ) {
    case GST_MESSAGE_EOS :
      g_print("End of stream\n");
      g_main_loop_quit(loop);
      break;
      
      
    case GST_MESSAGE_ERROR :{
      gchar *debug;
      GError *error;
      
      gst_message_parse_error(msg, &error, &debug);
      g_printerr("Error: %s\n", error->message);
      
      g_error_free(error);
      g_free(debug);
      
      g_main_loop_quit(loop);
      break;
    
    }
    default : break;
  }
  
  return TRUE;
}


gint main (gint argc, gchar *argv[]) {
  GMainLoop *loop;
  GstElement *play;
  GstBus *bus;
  
  char filename[] = "/Users/Jing/Dropbox/Jobs/OneCommunity/src/TestGStreamer/data/big_buck_bunny.ogv"; 
  gchar* uri = g_filename_to_uri(filename, NULL, NULL);
  
  /* init GStreamer */
  gst_init (&argc, &argv);
  loop = g_main_loop_new (NULL, FALSE);
  
  
  
  /* set up */
  play = gst_element_factory_make ("playbin", "play");
  g_object_set (G_OBJECT (play), "uri", uri, NULL);
  
  bus = gst_pipeline_get_bus (GST_PIPELINE (play));
  gst_bus_add_watch (bus, my_bus_callback, loop);
  gst_object_unref (bus);
  
  /*set state to playing*/
  gst_element_set_state (play, GST_STATE_PLAYING);
  
  
  /* now run */
  g_main_loop_run (loop);
  
  
  /* clean up */
  gst_element_set_state (play, GST_STATE_NULL);
  gst_object_unref (GST_OBJECT (play));
  
  
  g_free(uri);
  return 0;
}