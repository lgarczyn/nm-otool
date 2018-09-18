rm otool_diff ;
for f in /usr/lib/* /usr/bin/* obj/*
do
    echo $f
    echo $f >> otool_diff ;
    otool -dth $f  > /tmp/otool_a
    ./ft_otool -dth $f > /tmp/otool_b
    diff /tmp/otool_a /tmp/otool_b >> otool_diff
done