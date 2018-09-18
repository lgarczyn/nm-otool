rm nm_diff ;
for f in /usr/lib/* /usr/bin/* obj/*
do
    echo $f
    echo $f >> nm_diff ;
    nm $f  > /tmp/nm_a
    ./ft_nm $f > /tmp/nm_b
    diff /tmp/nm_a /tmp/nm_b >> nm_diff
done