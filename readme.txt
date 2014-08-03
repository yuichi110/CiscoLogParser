How to add component.

Abstract.
1. Create json file which contains command grouping info.
   Syntax is not difficult.
   Please see nexus.json first.

2. Create Parser for new product.
   You need to extends AbstractParser.

3. Define val of you product.
   Register new product to "ProductPicker" in constructer.

4. Change getParser function to return new Parser when
   new product is selected on ProductPicker.

Detail of Step 1.
You need to implement these function in  your Parser.
1. Constructer need to take JsonObject which contains
