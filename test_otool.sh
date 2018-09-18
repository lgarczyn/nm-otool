rm otool_diff ;
for f in /usr/lib/* /usr/bin/* obj/*
do
    echo $f
    echo $f >> otool_diff ;
    otool -tdh $f  > /tmp/otool_a
    ./ft_otool -dh $f > /tmp/otool_b
    diff /tmp/otool_a /tmp/otool_b >> otool_diff
done

for f in /usr/lib/* /usr/bin/* obj/*
do
    echo $f
    echo $f >> otool_diff ;
    otool -s __DWARF __debug_str $f  > /tmp/otool_a
    ./ft_otool -t -s __DWARF __debug_str $f > /tmp/otool_b
    diff /tmp/otool_a /tmp/otool_b >> otool_diff
done
