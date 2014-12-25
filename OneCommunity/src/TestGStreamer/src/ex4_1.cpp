#include <stdio.h>
#include <gst/gst.h>

// example print gstreamer version
int main(int argc, char* argv[]){
  const gchar *nano_str;
  
  guint major, minor, micro, nano;
  
  // It is also possible to call the gst_init function with two NULL arguments, 
  // in which case no command line options will be parsed by GStreamer.
  gst_init(&argc, &argv);
  
  gst_version(&major, &minor, &micro, &nano);
  
  if (nano == 1){
    nano_str="(CVS)";
  } else if (nano == 2){
    nano_str = "(Prerelease)";
  } else{
    nano_str = "";
  }
  
  printf("This program is linked against GStreamer %d.%d.%d %s \n", major, minor, micro, nano_str);
  
  return 0;
}