rm nm_diff ;
for f in /usr/lib/* /usr/bin/* obj/*
do
    echo $f
    echo $f >> nm_diff ;
    nm $f  > /tmp/nm_a
    ./ft_nm $f > /tmp/nm_b
    diff /tmp/nm_a /tmp/nm_b >> nm_diff
done

f=/usr/bin/audiodevice
echo $f
echo $f >> nm_diff ;
nm -n $f  > /tmp/nm_a
./ft_nm -n $f > /tmp/nm_b
diff /tmp/nm_a /tmp/nm_b >> nm_diff

f=/usr/bin/audiodevice
echo $f
echo $f >> nm_diff ;
nm -nr $f  > /tmp/nm_a
./ft_nm -nr $f > /tmp/nm_b
diff /tmp/nm_a /tmp/nm_b >> nm_diff

f=/usr/bin/audiodevice
echo $f
echo $f >> nm_diff ;
nm -p $f  > /tmp/nm_a
./ft_nm -p $f > /tmp/nm_b
diff /tmp/nm_a /tmp/nm_b >> nm_diff

f=/usr/bin/audiodevice
echo $f
echo $f >> nm_diff ;
nm -np $f  > /tmp/nm_a
./ft_nm -rp $f > /tmp/nm_b
diff /tmp/nm_a /tmp/nm_b >> nm_diff

f=/usr/bin/audiodevice
echo $f
echo $f >> nm_diff ;
nm -j $f  > /tmp/nm_a
./ft_nm -j $f > /tmp/nm_b
diff /tmp/nm_a /tmp/nm_b >> nm_diff