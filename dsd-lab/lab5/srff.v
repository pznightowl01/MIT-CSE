module srff(s,r,clk,reset,q);
input s,r,clk,reset;
output reg q;
always @(negedge clk)
begin 
if(!reset)
q<=1'b0; 
else 
begin 
if(s==0)begin 
if(r==0)
q<=q;
if(r==1)
q<=0;
end 
if(s==1)begin 
if(r==1)
q<=1;
if(r==1)
q<=1'bx; 
end 
end 
end 
endmodule 
