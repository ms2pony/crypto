FOR j := 0 to 1
	i := j*128
	tmp[255:0] := ((a[i+127:i] << 128)[255:0] OR b[i+127:i]) >> (imm8*8)
	dst[i+127:i] := tmp[127:0]
ENDFOR
dst[MAX:256] := 0