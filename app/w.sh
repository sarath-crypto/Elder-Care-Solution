sudo iw dev wlan0 interface add wlan1 type __ap
sleep 5
sudo nmcli connection up ecsysappi
ifconfig
