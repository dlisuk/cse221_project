echo -n "$1"
cat $1 | tail -n +3 | sort -n | head -n -20 | perl -e 'use List::Util qw(max min sum); @a=();while(<>){chomp;$sqsum+=$_*$_; push(@a,$_)}; $n=@a;$s=sum(@a);$a=$s/@a;$m=max(@a);$mm=min(@a);$std=sqrt($sqsum/$n-($s/$n)*($s/$n));$mid=int @a/2;@srtd=sort @a;if(@a%2){$med=$srtd[$mid];}else{$med=($srtd[$mid-1]+$srtd[$mid])/2;};print "\t$n\t$a\t$std\t$mm\t$m\n";'
