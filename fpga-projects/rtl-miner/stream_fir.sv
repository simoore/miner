module stream_fifo #(
    parameter int DATA_WIDTH = 32;
)(
    input logic clk,
    input logic [DATA_WIDTH-1:0] sig_i;
    output logic [DATA_WIDTH-1:0] sig_o;
);

always @(posedge clk) begin
end

end

endmodule