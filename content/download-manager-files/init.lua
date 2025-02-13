-- Display van data via MQ (Node-Red) v0.9
--Init  
DeviceID="ESP-12_MQTT_Display"  
Broker="192.168.9.187"  
mTopic = "energy/solar/actual"
topic = mTopic
myStr0 = ""
myStr1 = ""
myStr2 = "" -- place holders for the other lines
myStr3 = "" -- place holders for the other lines
myStr4 = ""
myStr5 = ""
myStr6 = ""
myStr7 = ""
gotEm = 0



-- setup SPI and connect display
function init_spi_display()
     -- Hardware SPI CLK  = GPIO14
     -- Hardware SPI MOSI = GPIO13
     -- Hardware SPI MISO = GPIO12 (not used)
     -- CS, D/C, and RES can be assigned freely to available GPIOs
     local cs  = 8 -- GPIO15, pull-down 10k to GND
     local dc  = 4 -- GPIO2
     local res = 0 -- GPIO16

     spi.setup(1, spi.MASTER, spi.CPOL_LOW, spi.CPHA_LOW, spi.DATABITS_8, 0)
     disp = u8g.ssd1306_128x64_spi(cs, dc, res)
end

-- graphic test components
function prepare()
     disp:setFont(u8g.font_6x10)
     disp:setFontRefHeightExtendedText()
     disp:setDefaultForegroundColor()
     disp:setFontPosTop()
end


function draw(void) 
--this gets called in an alarm loop to keep the display refreshed.
-- it prints the global strings myStr - so we just change those strings 
-- to change what is displayed
    prepare()
    disp:drawStr(0,0,myStr0)
    disp:drawStr(0,8,myStr1)
    disp:drawStr(0,16,myStr2)
    disp:drawStr(0,24,myStr3)
    disp:drawStr(0,32,myStr4)
    disp:drawStr(0,40,myStr5)
    disp:drawStr(0,48,myStr6)
    disp:drawStr(0,56,myStr7)
end


function loop(void) 
-- this is the loop that u8g apparently needs for display
  disp:firstPage() 
  repeat
    draw()
  until disp:nextPage() == false
 end

 function listen()
 -- this is where the ESP listens for mqtt messages and deals with displaying them
 m:on("message", function(conn, topic, data) 
 
   print(topic .. ":" ..data) 
   if (topic == "time") then 
      myStr0 = data
   elseif (topic == "energy/solar/actual") then
      myStr2 = "Solar Actual: "..data
   elseif (topic == "energy/solar/nactual") then
      myStr3 = "Net Import  : "..data 
   elseif (topic == "energy/solar/totalactual") then
      myStr4 = "Current Use : "..data
   elseif (topic == "energy/solar/today") then
        myStr5 = "Solar Today : "..data
   elseif (topic == "bitcoin/buy") then
        myStr7 = "Bitcoin: "..data
    end   
  end)               

 end -- of listen function
 
 function mqtt_sub()     -- here's where we subscribe to the topic we want to follow
    -- m:subscribe({["topic/0"]=0,["topic/1"]=1,topic2=2}, function(conn) print("subscribe success") end)
  -- m:subscribe("energy/solar/#",0, function(conn) print("subscribe success") end)
  m:subscribe({["energy/solar/#"]=0, ["bitcoin/#"]=0, ["time"]=0}, function(conn)   
  print("Mqtt Subscribed ") end)
      listen() --run the subscription function  
 
   -- end  
 end  

 m = mqtt.Client("ESP8266", 180, "vdsmq", "EvMQ2015#")  -- stuff to deal
 m:lwt("/lwt", "ESP8266", 0, 0)           -- with mqtt reconnects
 m:on("offline", function(con)   
    print ("Mqtt Reconnecting...")   
    tmr.alarm(1, 5000, 0, function() 
print ("should connect here...")   
      m:connect(Broker, 1883, 0, function(conn)   
        print("Mqtt Connected to:" .. Broker)  
        mqtt_sub() --run the subscription function  
      end)  
    end)  
 end)  

 -- below is initial set up of the mqtt connection
 tmr.alarm(0, 1000, 1, function()  
  if wifi.sta.status() == 5 and wifi.sta.getip() ~= nil then  
    tmr.stop(0)  
    m:connect(Broker, 1883, 0, function(conn)   
      print("Mqtt Connected to:" .. Broker)  
     mqtt_sub()
   end)  
  end  
 end)  
 
-- below is to set up the timer to keep hitting the display
init_spi_display()
tmr.alarm(3,1000,1,function()   
   disp:firstPage() 
   repeat
      draw()
   until disp:nextPage() == false 
end)

