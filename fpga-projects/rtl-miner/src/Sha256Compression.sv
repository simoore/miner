import Sha256Types::*;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This computes one iteration of the compression algorithm used in SHA256. Feed-in the message schedule array `wIn`
// and working variables `workingVarsIn` from the previous iteration, along with the appropriate rounding constant
// `k`. After one clock cycle, the working variables and the message schedule array for this iteration are 
// output on `workingVarsOut` and `wOut`.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
module Sha256Compression(
    input logic clk,
    input uint32_t k,
    input uint32_t wIn [0:15],
    input WorkingVars varsIn,

    output uint32_t wOut [0:15],
    output WorkingVars varsOut
);

    function uint32_t calcCh(input uint32_t x, input uint32_t y, input uint32_t z);
        return (x & y) ^ (~x & z);
    endfunction
    
    function uint32_t calcMaj(input uint32_t x, input uint32_t y, input uint32_t z);
        return (x & y) ^ (x & z) ^ (y & z);
    endfunction

    function uint32_t calcBigSigma0(input uint32_t x);
        return {varsIn.a[1:0], varsIn.a[31:2]} ^ {varsIn.a[12:0], varsIn.a[31:13]} ^ {varsIn.a[21:0], varsIn.a[31:22]};
    endfunction

    function uint32_t calcBigSigma1(input uint32_t x);
        return {x[5:0], x[31:6]} ^ {x[10:0], x[31:11]} ^ {x[24:0], x[31:25]};
    endfunction
    
    function uint32_t calcSmallSigma0(input uint32_t x);
        return {x[6:0], x[31:7]} ^ {x[17:0], x[31:18]} ^ {3'h0, x[31:3]};
    endfunction

    function uint32_t calcSmallSigma1(input uint32_t x);
        return {x[16:0], x[31:17]} ^ {x[18:0], x[31:19]} ^ {10'h0, x[31:10]};
    endfunction

    function uint32_t calcT1(input uint32_t e, input uint32_t f, input uint32_t g, input uint32_t h, 
            input uint32_t k, input uint32_t w);
        return h + calcBigSigma1(e) + calcCh(e, f, g) + k + w;
    endfunction

    uint32_t t1;
    uint32_t t2;

    assign t1 = calcT1(varsIn.e, varsIn.f, varsIn.g, varsIn.h, k, wIn[0]); 
    assign t2 = calcBigSigma0(varsIn.a) + calcMaj(varsIn.a, varsIn.b, varsIn.c);
    
    always_ff @(posedge clk) begin
        wOut[0:14] <= wIn[1:15];
        wOut[15] <= wIn[0] + calcSmallSigma0(wIn[1]) + wIn[9] + calcSmallSigma1(wIn[14]);
    
        varsOut.a <= t1 + t2;
        varsOut.b <= varsIn.a;
        varsOut.c <= varsIn.b;
        varsOut.d <= varsIn.c;
        varsOut.e <= varsIn.d + t1;
        varsOut.f <= varsIn.e;
        varsOut.g <= varsIn.f;
        varsOut.h <= varsIn.g;
    end

endmodule