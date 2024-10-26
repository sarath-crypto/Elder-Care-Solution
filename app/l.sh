while true
do
	tail -100 /var/log/syslog | grep ecsysapp
	ps -alx | grep ecsysapp
	sort -n log.txt  | uniq
        sleep 1
done

