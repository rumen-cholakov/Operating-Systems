#!/bin/bash
#Check if the number and type of parameters is correct.
if [[ $# -ne 1 || ! -d $1 ]];then
 echo "Invalid parameter given!"
 exit 1
fi

#Get the names of directories and check if they have a corresponding log file.
#If the drirectory has a log file add both of them to a corresponding array.
counter=0
while read dir;do
 if [[ $(find $1 -name *.log -printf "%f\n"|grep ^$dir.log$) ]];then
  arr_dir[$counter]=$dir
  arr_log[$counter]=$(echo "${arr_dir[$counter]}.log") 
  counter=$(( $counter + 1 ))
 fi
done < <(find $1 -type d -printf "%f\n"|tail -n +2)

#Pass through each pair of log file and directory and process them.
for i in ${!arr_dir[*]} ;do
#Create an array from the files in the current directory, sorted by ctime
 current_dir=$(echo "$1/${arr_dir[$i]}")
 pics=( $(ls $(echo "$current_dir") -ltc|tail -n +2|tr -s ' '|cut -f9 -d' '|tr '\n' ' ') )
 pic_counter=$(( ${#pics[*]} - 1))

#Random strings used to help in the procesing of the descriptions in the log files
 placeholder1=qazzxdrfvbhujmkolhlvfghkvtcghgksexracgsvtbexwcetzxxvzbykftydrhesxd
 placeholder2=lokmnhredzvsycytvferecuayehtxenujhgrfuftveujfyvretfnueyygvcdeszzaq

#Take the description of each .jpg file and create a new name
 while IFS=~ read -d'~' description;do
  file_info=$(echo "$description"|head -n 2|tr '\n' ' '|tr -s ' ')
  file_date=$(date -d "@$(echo $file_info|cut -f1 -d' ')" +%FT%H%M)
  file_description=$(echo $file_info|cut -f3- -d' '|tr [:punct:] ' '|tr -s ' '|tr ' ' '_')
  file_coordinates=$(echo $file_info|cut -f2 -d' ')
  file_longitude=$(echo $file_coordinates|cut -f1 -d',')
  file_latitude=$(echo $file_coordinates|cut -f2 -d',')

#Rename a .jpg file
  mv $(echo "$current_dir/${pics[$pic_counter]}") $(echo "$current_dir/${file_date}_$file_description.jpg")

#Adding coordinates to the exif of the .jpg files
  exiftool -overwrite_original -GPSLongitude="$file_longitude" $(echo "$current_dir/${file_date}_$file_description.jpg") > /dev/null 2> /dev/null
  exiftool -overwrite_original -GPSLatitude="$file_latitude" $(echo "$current_dir/${file_date}_$file_description.jpg") > /dev/null 2> /dev/null
  pic_counter=$(( $pic_counter - 1 ))

#A series of transformations aiming to prepare the contents of the log file for processing
 done < <(cat $(echo "$1/${arr_log[$i]}")|tr [:upper:] [:lower:]|
 sed "s/\./$placeholder1/g; s/,/$placeholder2/g; s/[[:punct:]]//g; s/$placeholder1/\./g; s/$placeholder2/,/g"|
 tr -s ' '|awk 'BEGIN{RS="\n\n" ; ORS="~";}{ print }')
done
