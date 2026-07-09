 `timescale 1ns/1ns 
`include "srff.v"


module srff_tb();
reg s,r,clk,reset; 
wire w; 


srff test(s,r,clk,reset,q); 
initial 
begin 
$dumpfile("srff_tb.vcd");
$dumpvars(0,srff_tb);
clk=1'b1;
forever#10 clk=~clk;
end 
initial begin
s=1;r=0;reset=1;#20;
s=0;r=0;reset=0;#20;
s=0;r=1;reset=1;#20;
s=0;r=0;reset=1;#20;
s=1;r=1;reset=1;#20;
$display("test complete");
$finish;
end 
endmodule 
