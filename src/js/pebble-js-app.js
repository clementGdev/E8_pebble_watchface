 Pebble.addEventListener("ready",
  function(e) {
    //console.log("PebbleKit JS ready!");
  }
);


Pebble.addEventListener("showConfiguration",
  function(e) {
    //Load the remote config page
    Pebble.openURL("https://dl.dropbox.com/s/shxosvqy22040lj/E8_config.html");//"https://dl.dropboxusercontent.com/u/10824180/pebble%20config%20pages/sdktut9-config.html");
  }
);


Pebble.addEventListener("webviewclosed",
  function(e) {
    //Get JSON dictionary
     console.log("Configuration window returned");
    var configuration = JSON.parse(decodeURIComponent(e.response));
    console.log("Configuration window returned: " + JSON.stringify(configuration));
 
    //Send to Pebble, persist there
    Pebble.sendAppMessage(
      {"KEY_INVERT": configuration.invert, "KEY_BATTERY": configuration.battery},
      function(e) {
        //console.log("Sending settings data...");
      },
      function(e) {
        //console.log("Settings feedback failed!");
      }
    );
  }
);