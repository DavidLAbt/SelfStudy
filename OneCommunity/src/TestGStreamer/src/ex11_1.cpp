/* 
 * based on ex10_1.cpp
 */

#include <gst/gst.h>
#include <glib.h>

/* message handle function */
static gboolean bus_call(GstBus *bus, GstMessage * msg, gpointer data) {
  
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

/* dynamic pad*/
static void on_pad_added(GstElement *element, GstPad *pad, gpointer data) {
  GstPad *sinkpad;
  
  GstElement *decoder = (GstElement *) data; // the element connect to element
  
  g_print("Dynamic pad created, linking demuxer/decorder \n ");
  
  // get the sink pad
  sinkpad = gst_element_get_static_pad(decoder, "sink");
  
  // link pad
  gst_pad_link(pad, sinkpad);
  
  gst_object_unref(sinkpad);
  
}

int main(int argc, char* argv[]) {
  GMainLoop *loop;
  
  GstElement *pipeline, *source, *demuxer, *decoder, *conv, *sink;
  GstBus *bus;
  guint bus_watch_id;
  
  char filename[] = "./data/Epoq-Lepidoptera.ogg"; 
    
  /* Check input arguments */
  /*
  if (argc != 2) {
    g_printerr ("Usage: %s <Ogg/Vorbis filename>\n", argv[0]);
    return -1;
  }
  */
  
  /* Initialisation */
  gst_init (&argc, &argv);
  

  /*create pipeline*/
  pipeline = gst_pipeline_new("audio_player");
  
  
  /* create elements of the pipeline*/
  source  = gst_element_factory_make("filesrc",         "filesource");
  demuxer = gst_element_factory_make("oggdemux",        "ogg-demuxer");
  decoder = gst_element_factory_make("vorbisdec",       "vorbis-decoder");
  conv    = gst_element_factory_make("audioconvert",    "converter");
  sink    = gst_element_factory_make("autoaudiosink",  "audio-output");

  
  if (!pipeline || !source || !demuxer || !decoder || !conv || !sink) {
    g_printerr ("One element could not be created. Exiting.\n");
    return -1;
  }
  
  /* Set up the pipeline */
  
  /* Set the input filename to the source element */
  g_object_set(G_OBJECT(source), "location", filename, NULL);
  
  
  /* add a message handler for the pipeline*/
  loop = g_main_loop_new (NULL, FALSE);                 // new main loop 
  bus = gst_pipeline_get_bus( GST_PIPELINE(pipeline) ); //get bus
  bus_watch_id = gst_bus_add_watch(bus, bus_call, loop);//attach handler
  gst_object_unref (bus);
  
  
  /* we add all elements into the pipeline */
  /* file-source | ogg-demuxer | vorbis-decoder | converter | alsa-output */
  gst_bin_add_many (GST_BIN (pipeline), source, demuxer, decoder, conv, sink, NULL);
  
  
  /* we link the elements together */
  /* file-source -> ogg-demuxer ~> vorbis-decoder -> converter -> alsa-output */
  gst_element_link (source, demuxer);
  gst_element_link_many (decoder, conv, sink, NULL);
  
  g_signal_connect (demuxer, "pad-added", G_CALLBACK (on_pad_added), decoder);
  
  /* Set the pipeline to "playing" state*/
  g_print ("Now playing: %s\n", filename);
  gst_element_set_state (pipeline, GST_STATE_PLAYING);
  
  
  /* run loop */
  g_print("Running...\n");
  g_main_loop_run(loop);
  
  /* Out of the main loop, clean up nicely */
  g_print ("Returned, stopping playback\n");
  gst_element_set_state (pipeline, GST_STATE_NULL);
  
  /* clean */
  g_print ("Deleting pipeline\n");
  gst_object_unref (GST_OBJECT (pipeline));
  g_source_remove (bus_watch_id);
  g_main_loop_unref (loop);
  
  return 0;
}