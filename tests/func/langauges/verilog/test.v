module inst(input in)
endmodule

module top()
    reg r;
    assign r = inst(r);
endmodule
