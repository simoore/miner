`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11.10.2023 23:25:02
// Design Name: 
// Module Name: ExampleTestbench
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module ExampleTestbench(

    );
endmodule

    class transaction;
     randc bit [3:0] a;
     randc bit [3:0] b;
      bit [4:0] sum;
      
      
       function void display();
        $display("a : %0d \t b: %0d \t sum : %0d",a,b,sum);
      endfunction
      
      
    endclass
     
    interface add_if;
      logic [3:0] a;
      logic [3:0] b;
      logic [4:0] sum;
      logic clk;
    endinterface
     
     
    class monitor;
      
      mailbox #(transaction) mbx;
      transaction trans;
      virtual add_if aif;
      
      function new(mailbox #(transaction) mbx);
        this.mbx = mbx;
      endfunction
      
      task run();
        trans = new();
        forever begin
          repeat(2) @(posedge aif.clk);
          trans.a = aif.a;
          trans.b = aif.b;
          trans.sum = aif.sum;
          $display("-------------------------");
          $display("[MON] : DATA SENT TO SCOREBOARD");
          trans.display();
          mbx.put(trans);
        end
      endtask
      
      
    endclass
     
     
    class scoreboard;
      
       mailbox #(transaction) mbx;
      transaction trans;
      
        function new(mailbox #(transaction) mbx);
        this.mbx = mbx;
       endfunction
      
      task compare(input transaction trans);
        if((trans.sum) == (trans.a + trans.b)) 
          $display("[SCO] : Sum Result Matched");
        else
          $error("[SCO] : Result Mismatched");
      endtask
     
      task run();
        forever begin
          mbx.get(trans);
          $display("[SCO] : DATA RCVD FROM MONITOR");
          trans.display();
          compare(trans);
          $display("-------------------------");
          #40;
        end
      endtask
      
      
    endclass
     
     
     
     
     
     
     
     
    module tb;
      
     add_if aif();
      monitor mon;
      scoreboard sco;
      mailbox #(transaction) mbx;
     
      
     
     
      
      add dut (aif.a, aif.b, aif.sum, aif.clk );
     
     
      initial begin
        aif.clk <= 0;
      end
      
      always #10 aif.clk <= ~aif.clk;
     
      initial begin
        for(int i = 0; i < 20 ; i++) begin
          repeat(2) @(posedge aif.clk);
          aif.a <= $urandom_range(0,15);
          aif.b <= $urandom_range(0,15);    
        end
      end
      
      initial begin
        mbx = new();
        mon = new(mbx);
        sco = new(mbx);
        mon.aif = aif;
        
      end
                  
        initial begin         
          fork        
            mon.run();
            sco.run();
          join
        end
      initial begin
        $dumpfile("dump.vcd"); 
        $dumpvars;  
        #450;
        $finish();
      end
      
    endmodule