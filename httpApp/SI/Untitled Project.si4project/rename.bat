SET src=dmx512-01
SET dst=esp32_http_format
#SET sipath=D:\ESP32\esp-idf-0421\app-event-223\SI

RENAME %src%.bookmarks.xml      %dst%.bookmarks.xml
RENAME %src%.sip_sym  %dst%.sip_sym
RENAME %src%.sip_xab  %dst%.sip_xab
RENAME %src%.sip_xad  %dst%.sip_xad
#RENAME %src%.sip_xc   %dst%.sip_xc
#RENAME %src%.sip_xf   %dst%.sip_xf
RENAME %src%.sip_xm   %dst%.sip_xm
R#ENAME %src%.sip_xr   %dst%.sip_xr
RENAME %src%.sip_xsb  %dst%.sip_xsb
RENAME %src%.sip_xsd  %dst%.sip_xsd
RENAME %src%.siproj   %dst%.siproj
RENAME %src%.siproj_settings.xml      %dst%.siproj_settings.xml
RENAME %src%.siwork   %dst%.siwork
RENAME %src%.snippets.xml      %dst%.snippets.xml

#copy *.* %sipath%

ECHO done    
