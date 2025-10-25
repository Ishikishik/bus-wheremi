//頭4.8(2.4)(2.9)mmネジ3.4(1.7)mmナット5.8(2.9)(3.4)mm
//頭4.8(2.4)(2.9)mmネジ3.4(1.7)mmナット5.8(2.9)(3.4)mm
difference() {
    union(){

    // 外枠（厚み6.5mm）
    translate([0,0,0])
    cube([41, 29.5,77 ], center = true);//外装
//ESP32--------------------------
    translate([41/2-4.9, 29.5/2, -77/2 + 16.5])
    rotate([-90,0,0])//ネジ穴＋出っ張り
    difference(){
        cylinder(h = 3, r = 2.5, center = false);
        cylinder(h = 3, r = 1.2, center = false);
    }
    translate([41/2-4.9, 29.5/2, -77/2 + 16.5 +12.1])
    rotate([-90,0,0])//ネジ穴＋出っ張り
    difference(){
        cylinder(h = 3, r = 2.3, center = false);
        cylinder(h = 3, r = 1.2, center = false);

    }
        translate([41/2-4.9, 29.5/2, -77/2 + 16.5 + 32.4])
    rotate([-90,0,0])//ネジ穴＋出っ張り
    difference(){
        cylinder(h = 3, r = 2.5, center = false);
        cylinder(h = 3, r = 1.2, center = false);
    }
    translate([41/2-4.9, 29.5/2, -77/2 + 16.5 + 52.8])
    rotate([-90,0,0])//ネジ穴＋出っ張り
    difference(){
        cylinder(h = 3, r = 2.5, center = false);
        cylinder(h = 3, r = 1.2, center = false);

    }
            translate([ 41/2-(4.9 + 32.6), 29.5/2, -77/2 + 16.5])
    rotate([-90,0,0])//ネジ穴＋出っ張り
    difference(){
        cylinder(h = 3, r = 2.5, center = false);
        cylinder(h = 3, r = 1.2, center = false);
    }
    translate([ 41/2-(4.9 + 32.6), 29.5/2, -77/2 + 16.5 + 52.8])
    rotate([-90,0,0])//ネジ穴＋出っ張り
    difference(){
        cylinder(h = 3, r = 2.5, center = false);
        cylinder(h = 3, r = 1.2, center = false);

    }
//ESP32--------------------------
//LSI--------------------------
    translate([ -41/2, -29.5/2 + 3.6, -77/2 + 6.8])
    rotate([0,-90,0])//ネジ穴＋出っ張り
    difference(){
        cylinder(h = 3, r = 2.5, center = false);
        cylinder(h = 3, r = 1.2, center = false);

    }

        translate([ -41/2,-29.5/2 + 3.6, -77/2 + 6.8 + 57.8])
    rotate([0,-90,0])//ネジ穴＋出っ張り
    difference(){
        cylinder(h = 3, r = 2.5, center = false);
        cylinder(h = 3, r = 1.2, center = false);

    }

        translate([ -41/2, -29.5/2 + 3.6 + 19.9, -77/2 + 6.8])
    rotate([0,-90,0])//ネジ穴＋出っ張り
    difference(){
        cylinder(h = 3, r = 2.5, center = false);
        cylinder(h = 3, r = 1.2, center = false);

    }

        translate([ -41/2, -29.5/2 + 3.6 + 19.9, -77/2 + 6.8 + 57.8])
    rotate([0,-90,0])//ネジ穴＋出っ張り
    difference(){
        cylinder(h = 3, r = 2.5, center = false);
        cylinder(h = 3, r = 1.2, center = false);

    }
    //LSI--------------------------
    //GPS--------------------------
            translate([41/2, 29.5/2 - 14.5, -77/2 + 4.0])
    rotate([0,90,0])//ネジ穴＋出っ張り
    difference(){
        cylinder(h = 4.7, r = 2.5, center = false);
        cylinder(h = 4.7, r = 1.2, center = false);

    }

        translate([41/2, 29.5/2 - (14.5 + 9.4), -77/2 + 4.0 + 28])
    rotate([0,90,0])//ネジ穴＋出っ張り
    difference(){
        cylinder(h = 3, r = 2.5, center = false);
        cylinder(h = 3, r = 1.2, center = false);

    }

    //GPS--------------------------
    //フタ-------------------------
    difference(){
            translate([41/2 -(41 + 9 + 13.4 + 2.7 * 2)/2 + 9 + 2.7, -29.5/2 + (29.5 + 11.2 + 2.7 *2)/2 - 2.7,77/2 - 12.7/2+2.7])
            cube([41 + 9 + 13.4 + 2.7 * 2, 29.5 + 11.2 + 2.7 *2, 12.7], center = true);

            translate([41/2 -(41 + 9 + 13.4 + 2.7 * 2)/2 + 9 + 2.7, -29.5/2 + (29.5 + 11.2 + 2.7 *2)/2 - 2.7,77/2 - 12.7/2])
            cube([41 + 9 + 13.4 + 2.7 * 2 - 2.8, 29.5 + 11.2 + 2.7 *2 - 1.4, 12.7], center = true);

            translate([0, -10,77/2 - 12.7/2])
                cube([38, 28,12.7], center = true);//くりぬき


    }



    }

    translate([0,-1.5,0])
    cube([38, 28,77 ], center = true);//くりぬき

    translate([41/2-3.3, 29.5/2-9.4/2,0])
    cube([6.6, 9.4, 16], center = true);//端子くりぬき(xz面) 




/*
    //本体部
    translate([0,0,1.5])
    cube([90, 51,8.8], center = true);

    translate([90/2-21.4,-(64/2)+10,0])
    cube([6.5, 3,100], center = true);//端子

    translate([90/2-24.9,-(64/2)+32.5,0])
    cube([10.4, 11,100], center = true);//ロータリースイッチ

    translate([90/2-28.5,64/2,3.1])
    cube([19, 30,5.7], center = true);//アンテナ


    //ネジ
    translate([95/2-3,60/2-1,-20])
    cylinder(h = 100, r = 1.7, center = false);

    translate([-(95/2-3),60/2-1,-20])
    cylinder(h = 100, r = 1.7, center = false);

    translate([95/2-3,-(60/2-1),-20])
    cylinder(h = 100, r = 1.7, center = false);

    translate([-(95/2-3),-(60/2-1),-20])
    cylinder(h = 100, r = 1.7, center = false);

        //ネジ頭
    translate([95/2-3,60/2-1,-(11.8/2)])
    cylinder(h = 2, r = 3, center = false);

    translate([-(95/2-3),60/2-1,-(11.8/2)])
    cylinder(h = 2, r = 3, center = false);

    translate([95/2-3,-(60/2-1),-(11.8/2)])
    cylinder(h = 2, r = 3, center = false);

    translate([-(95/2-3),-(60/2-1),-(11.8/2)])
    cylinder(h = 2, r = 3, center = false);
*/


   
}