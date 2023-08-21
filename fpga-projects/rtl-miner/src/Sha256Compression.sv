import Sha256Types::*;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This computes one iteration of the compression algorithm used in SHA256. Feed-in the message schedule array `wIn`
// and working variables `workingVarsIn` from the previous iteration, along with the appropriate rounding constant
// `k`. After one clock cycle, the working variables and the message schedule array for this iteration are 
// output on `workingVarsOut` and `wOut`.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
module Sha256Compression(
    input logic clk,
    input logic [31:0] k,
    input logic [31:0] wIn [0:15],
    input WorkingVars varsIn,

    output logic [31:0] wOut [0:15],
    output WorkingVars varsOut
);

logic [31:0] bigSigma1, ch, temp1, bigSigma0, maj, temp2, smallSigma0, smallSigma1;

assign bigSigma1 = {varsIn.e[5:0], varsIn.e[31:6]} ^ {varsIn.e[10:0], varsIn.e[31:11]} ^ 
    {varsIn.e[24:0], varsIn.e[31:25]};
assign ch = (varsIn.e & varsIn.f) ^ (~varsIn.e & varsIn.g);
assign temp1 = varsIn.h + bigSigma1 + ch + k + wIn[0];
assign bigSigma0 = {varsIn.a[1:0], varsIn.a[31:2]} ^ {varsIn.a[12:0], varsIn.a[31:13]} ^ 
    {varsIn.a[21:0], varsIn.a[31:22]};
assign maj = (varsIn.a &varsIn. b) ^ (varsIn.a & varsIn.c) ^ (varsIn.b & varsIn.c);
assign temp2 = bigSigma0 + maj;

assign smallSigma0 = {wIn[1][6:0], wIn[1][31:7]} ^ {wIn[1][17:0], wIn[1][31:18]} ^ {3'h0, wIn[1][31:3]};
assign smallSigma1 = {wIn[14][16:0], wIn[14][31:17]} ^ {wIn[14][18:0], wIn[14][31:19]} ^ {10'h0, wIn[14][31:10]};

always_ff @(posedge clk) begin
    wOut[0:14] <= wIn[1:15];
    wOut[15] <= wIn[0] + smallSigma0 + wIn[9] + smallSigma1;

    varsOut.a <= temp1 + temp2;
    varsOut.b <= varsIn.a;
    varsOut.c <= varsIn.b;
    varsOut.d <= varsIn.c;
    varsOut.e <= varsIn.d + temp1;
    varsOut.f <= varsIn.e;
    varsOut.g <= varsIn.f;
    varsOut.h <= varsIn.g;
end

endmodule