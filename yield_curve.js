function drawGraph( dataArr ){  
    var canvas = document.getElementById( "testCanvas" );  
    var context = canvas.getContext( "2d" );  
  
    var GRAPH_TOP = 25;  
    var GRAPH_BOTTOM = 375;  
    var GRAPH_LEFT = 25;  
    var GRAPH_RIGHT = 475;  
  
    var GRAPH_HEIGHT = 350;  
    var GRAPH_WIDTH = 450;  
  
    var arrayLen = dataArr.length;  
  
    var largest = 0;  
    for( var i = 0; i < arrayLen; i++ ){  
        if( dataArr[ i ] > largest ){  
            largest = dataArr[ i ];  
        }  
    }  
  
    context.clearRect( 0, 0, 500, 400 );  
    // set font for fillText()  
    context.font = "16px Arial";  
       
    // draw X and Y axis  
    context.beginPath();  
    context.moveTo( GRAPH_LEFT, GRAPH_BOTTOM );  
    context.lineTo( GRAPH_RIGHT, GRAPH_BOTTOM );  
    context.lineTo( GRAPH_RIGHT, GRAPH_TOP );  
    context.stroke();  
       
    // draw reference line  
    context.beginPath();  
    context.strokeStyle = "#BBB";  
    context.moveTo( GRAPH_LEFT, GRAPH_TOP );  
    context.lineTo( GRAPH_RIGHT, GRAPH_TOP );  
    // draw reference value for hours  
    context.fillText( largest, GRAPH_RIGHT + 15, GRAPH_TOP);  
    context.stroke();  
   
    // draw reference line  
    context.beginPath();  
    context.moveTo( GRAPH_LEFT, ( GRAPH_HEIGHT ) / 4 * 3 + GRAPH_TOP );  
    context.lineTo( GRAPH_RIGHT, ( GRAPH_HEIGHT ) / 4 * 3 + GRAPH_TOP );  
    // draw reference value for hours  
    context.fillText( largest / 4, GRAPH_RIGHT + 15, ( GRAPH_HEIGHT ) / 4 * 3 + GRAPH_TOP);  
    context.stroke();  
   
    // draw reference line  
    context.beginPath();  
    context.moveTo( GRAPH_LEFT, ( GRAPH_HEIGHT ) / 2 + GRAPH_TOP );  
    context.lineTo( GRAPH_RIGHT, ( GRAPH_HEIGHT ) / 2 + GRAPH_TOP );  
    // draw reference value for hours  
    context.fillText( largest / 2, GRAPH_RIGHT + 15, ( GRAPH_HEIGHT ) / 2 + GRAPH_TOP);  
    context.stroke();  
   
    // draw reference line  
    context.beginPath();  
    context.moveTo( GRAPH_LEFT, ( GRAPH_HEIGHT ) / 4 + GRAPH_TOP );  
    context.lineTo( GRAPH_RIGHT, ( GRAPH_HEIGHT ) / 4 + GRAPH_TOP );  
    // draw reference value for hours  
    context.fillText( largest / 4 * 3, GRAPH_RIGHT + 15, ( GRAPH_HEIGHT ) / 4 + GRAPH_TOP);  
    context.stroke();  
  
    // draw titles  
    context.fillText( "Maturity", GRAPH_RIGHT / 3, GRAPH_BOTTOM + 50);  
    context.fillText( "Rate", GRAPH_RIGHT + 30, GRAPH_HEIGHT / 2);  
  
    context.beginPath();  
    context.lineJoin = "round";  
    context.strokeStyle = "black";  
  
   // var maturities = [ "3mo", "6mo", "1yr", "2yr", "5yr", "10yr", "30yr" ];

    context.moveTo( GRAPH_LEFT, ( GRAPH_HEIGHT - dataArr[ 0 ] / largest * GRAPH_HEIGHT ) + GRAPH_TOP );  
    // draw reference value for day of the week  
    // context.fillText( maturities[0], 15, GRAPH_BOTTOM + 25);  
    for( var i = 1; i < arrayLen; i++ ){  
        context.lineTo( GRAPH_RIGHT / arrayLen * i + GRAPH_LEFT, ( GRAPH_HEIGHT - dataArr[ i ] / largest * GRAPH_HEIGHT ) + GRAPH_TOP );  
        // draw reference value for day of the week  
        // context.fillText( ( maturities[i] ), GRAPH_RIGHT / arrayLen * i, GRAPH_BOTTOM + 25);  
    }  
    context.stroke();  
}   
   
// test graph  
// var testValues = [ 2, 1.96, 1.86, 1.66, 1.57, 1.68, 2.15 ];  
window.onLoad = drawGraph( testValues );
