a = SharedArray{Float64}(2900000)
b = SharedArray{Float64}(2900000)
c = SharedArray{Float64}(2900000)
d = SharedArray{Float64}(2900000)
e = SharedArray{Float64}(1)
f = open("PhiPi2DimSqrtS.dat","w")
e[1] = 0
@everywhere include("basdevant-berger-cm.jl")
@everywhere using PhaseSpace
      @sync @parallel for i = 200:3099
          
      	  iscale = (i / 1000.0)
	  for j = -999:0
	  jscale = (j / 1000.0)
	  sqrtS = complex(iscale,jscale)
	  S = sqrtS^2
	  result = bbcm(real(S),imag(S),0.493677,0.493677,0.13957,0.13957,1.01947,0.0210854,0.13957,0.0,0.0)
	  a[(i-200)*1000-j+1] = result[2]
	  b[(i-200)*1000-j+1] = result[1]
	  c[(i-200)*1000-j+1] = iscale
	  d[(i-200)*1000-j+1] = jscale
	  if j % 1000 == 0 
	     e[1] = e[1]+1000
	     println(e[1])
	   end
	 end
      end  
 for k = 1:2900000
  out = string(c[k], " ", d[k], " ", b[k], " ", a[k], "\n")
  write(f,out)
 
end
close(f)

