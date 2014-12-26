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


static void cb_pad_added(GstElement *dec, GstPad *pad, gpointer data) {
  GstCaps *caps,
  GstStructure *s;
  
  const gchar* name;
  GstPadTemplate *templ;
  GstElementClass *klass;
  
  /* check media type */
  caps = gst_pad_query_caps(pad, NULL);
  
}

gint main(gint argc, gchar* argv[]){
  GMainLoop *loop;
  GstElement *dec;
  GstBus *bus;
  
  
  /* init gstreamer */
  gst_init(&argc, &argv);
  
  
  loop = g_main_loop_new(NULL, FALSE);
  
  
  
  /* build pipeline */
  pipeline = gst_pipeline_new("pipeline");
  
  
  bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
  gst_bus_add_watch(bus, my_bus_callback, loop);
  gst_object_unref (bus);
  
  
  dec = gst_element_factory_make("uridecodebin", "source");
  
  
}
