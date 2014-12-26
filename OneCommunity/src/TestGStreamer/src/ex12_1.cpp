
/*
 * Extract tags from a file and print them
 */


#include <gst/gst.h>

static void print_one_tag(const GstTagList *list, const gchar* tag, gpointer user_data){
  int i, num;
  
  num = gst_tag_list_get_tag_size(list, tag);
  
  for (i = 0; i < num; ++i ){
    
    const GValue *val;
    
    val = gst_tag_list_get_value_index(list, tag, i);
    
     g_print ("\t%20s : tag of type '%s'\n", tag, G_VALUE_TYPE_NAME (val));
     
     
    if ( G_VALUE_HOLDS_STRING(val) ) { // string 
      g_print("\t%20s: %s\n", tag, g_value_get_string(val) );          
    } else if ( G_VALUE_HOLDS_UINT(val) ) { // unsigned int
      g_print("\t%20s: %u\n", tag, g_value_get_uint(val) );  
    } else if ( G_VALUE_HOLDS_DOUBLE(val) ) { // double
      g_print("\t%20s: %g\n", tag, g_value_get_double(val) );  
    } else if ( G_VALUE_HOLDS_BOOLEAN(val) ) { // boolean
      g_print("\t%20s: %s\n", tag, g_value_get_boolean(val) ? "true" : "false" );  
    } else if ( GST_VALUE_HOLDS_BUFFER(val) ) { //buffer
      GstBuffer *buf = gst_value_get_buffer(val);
      guint buffer_size = gst_buffer_get_size(buf);
      g_print ("\t%20s : buffer of size %u\n", tag, buffer_size);
    } else {
      g_print ("Unprocessing type");
    } // end if-else
    
  } // end for
  
  
}

static void on_new_pad (GstElement * dec, GstPad * pad, GstElement * fakesink)
{
  GstPad *sinkpad;
  sinkpad = gst_element_get_static_pad (fakesink, "sink");
  if (!gst_pad_is_linked (sinkpad)) {
    if (gst_pad_link (pad, sinkpad) != GST_PAD_LINK_OK)
      g_error ("Failed to link pads!");
  }
  
  gst_object_unref (sinkpad);
}

int main (int argc, char ** argv)
{
  GstElement *pipe, *dec, *sink;
  GstMessage *msg;
  
  
  char filename[] = "/Users/Jing/Dropbox/Jobs/OneCommunity/src/TestGStreamer/data/Epoq-Lepidoptera.ogg"; 
  gchar* uri = g_filename_to_uri(filename, NULL, NULL);
  gst_init (&argc, &argv);
  
  
  pipe = gst_pipeline_new ("pipeline");
  
  /* a bin including source and decode elements */
  dec = gst_element_factory_make ("uridecodebin", NULL);
  g_object_set (dec, "uri", uri, NULL);
  
  gst_bin_add (GST_BIN (pipe), dec);
  
  /* fake sink element */
  sink = gst_element_factory_make ("fakesink", NULL);
  gst_bin_add (GST_BIN (pipe), sink);
  
  /* add dynamic link */
  g_signal_connect (dec, "pad-added", G_CALLBACK (on_new_pad), sink);
  
  gst_element_set_state (pipe, GST_STATE_PAUSED);
  
  while (TRUE) {
    GstTagList *tags = NULL;
    
    /* Get a message from the bus whose type matches the message type mask types , 
     * waiting up to the specified timeout (and discarding any messages that 
     * do not match the mask provided).
     */
    msg = gst_bus_timed_pop_filtered(GST_ELEMENT_BUS(pipe), GST_CLOCK_TIME_NONE, (GstMessageType) (GST_MESSAGE_ASYNC_DONE | GST_MESSAGE_TAG | GST_MESSAGE_ERROR) );
    
    if (GST_MESSAGE_TYPE (msg) != GST_MESSAGE_TAG) {/* error or async_done */
      break;
    }
    
    /*get tag*/
    gst_message_parse_tag (msg, &tags);
    
    /*print tag information*/
    g_print ("Got tags from element %s:\n", GST_OBJECT_NAME (msg->src));
    gst_tag_list_foreach (tags, print_one_tag, NULL);
    g_print ("\n");
    
    /* clean */;
    gst_tag_list_unref (tags);
   
    
  }
  
  if (GST_MESSAGE_TYPE (msg) == GST_MESSAGE_ERROR){
    g_error ("Got error");
  }
  
  
  
  gst_message_unref (msg);
  gst_element_set_state (pipe, GST_STATE_NULL);
  gst_object_unref (pipe);
  g_free(uri);
  return 0;
}