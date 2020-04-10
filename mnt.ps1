copy -r -Force E:/* ~/Desktop/zenithos/src/
del ~/Desktop/zenithos/*.iso
move ~/Desktop/zenithos/src/Tmp/MyDistro.ISO.C ~/Desktop/zenithos/Zenith-latest-$(get-date -Format "yyyy-MM-dd-HH_mm_ss").iso
