//The following example 1 shows how to create an element named source from the element factory named
//fakesrc. It checks if the creation succeeded. After checking, it unrefs the element.

#include <gst/gst.h>

int main(int argc, char* argv[]) {
  
  
  GstElementFactory *factory;
  GstElement *element;
  gchar *name;
  
  /* init Gstreamer */
  gst_init(&argc, &argv);
  
  /* create an element */
  // the first method
  // element = gst_element_factory_make("fakesrc", "source");
  //
  // the second method 
  // find the factory
  factory = gst_element_factory_find ("fakesrc");
  if (!factory) {
    g_print ("You don’t have the ’fakesrc’ element installed!\n");
    return -1;
  }
  
  element = gst_element_factory_create (factory, "source");
  if (!element) {
    g_print("Failed to create element of type 'fackesrc'!\n");
    return -1;
  } 
  
  g_print("Successful to create element of type 'fakesrc'\n");
    
  /*get element name*/
  g_object_get(G_OBJECT(element), "name", &name, NULL);
  g_print("The name of the fakesrc element is '%s'.\n", name);
  g_free(name);
  
  /* display factory information */
  g_print ("The '%s' element is a member of the category %s.\n"
  "Description: %s\n",
  gst_plugin_feature_get_name (GST_PLUGIN_FEATURE (factory)),
  gst_element_factory_get_metadata (factory, GST_ELEMENT_METADATA_KLASS),
  gst_element_factory_get_metadata (factory, GST_ELEMENT_METADATA_DESCRIPTION));
  
  gst_object_unref(GST_OBJECT(element));
  return 0;
}