while true
do
	tail -100 /var/log/syslog | grep ecsysapp
	ps -alx | grep ecsysapp
        sleep 1
done

