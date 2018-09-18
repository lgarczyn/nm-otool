rm otool_diff ;
for f in /usr/bin/*
do
    echo $f
    echo $f >> otool_diff ;
    otool -t $f  > /tmp/otool_a
    ./ft_otool $f > /tmp/otool_b
    diff /tmp/otool_a /tmp/otool_b >> otool_diff
done