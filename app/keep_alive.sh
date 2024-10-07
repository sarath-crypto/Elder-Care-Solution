while true
do 
	cmd=$(pgrep ecsysapp)
	if [ -z "$cmd" ]; then
		/home/ecsys/v4/ecsysapp /home/ecsys/v4/config.ini
	fi
	sleep 30
done
