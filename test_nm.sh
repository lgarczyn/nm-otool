rm nm_diff ;
for f in /usr/bin/*
do
    echo $f
    echo $f >> nm_diff ;
    nm $f  > /tmp/a
    ./ft_nm $f > /tmp/b
    diff /tmp/a /tmp/b >> nm_diff
done