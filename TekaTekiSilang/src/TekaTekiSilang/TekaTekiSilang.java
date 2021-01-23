/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package TekaTekiSilang;

/**
 *
 * @author Fendy
 */
 
public class TekaTekiSilang {
    public static int x = 0;
    public  static int y = 0;
   
    public static void ct(char map[][]){
        for (int i = 0; i < 50; i++) {
            for (int j = 0; j < 50; j++) {
                System.out.print(map[i][j]);
                System.out.print(" ");
            }
            System.out.println("");
        }
        System.out.println("");
    }
    
    public static void isimap(char map[][]) {
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                map[i][j]= '_';
            }
        }
    }
   
    
    public static boolean cek (String jawaban[], int ctr, char map[][]){
        int a = 0;
        boolean hasil = false;
        if(ctr == 0){
            for (int i = 0; i < jawaban[ctr].length(); i++) {      
                map[y][i] = jawaban[ctr].charAt(i);

            }
            hasil = true;
        }
        else{
            if(ctr % 2 == 0){
                System.out.println("mendatar");
                do{  
                    //char tmp = jawaban[ctr-1].charAt(0);
                    System.out.println("looping "+a);
                    if(map[a][x] == jawaban[ctr].charAt(0)){                  
                        y = a;
                        hasil = true;
                    } else{
                        a++;
                        hasil = false;
                       // cek(jawaban,ctr-a,map);
                    }
                }while(!hasil && a < jawaban[ctr-1].length());
            
               
            }else if(ctr % 2 == 1){
                System.out.println("menurun");
                //char tmp = jawaban[ctr-1].charAt(0);
                do{ 
                    System.out.println("looping "+a);
                    if(map[y][a] == jawaban[ctr].charAt(0)){                      
                       x = a;
                       hasil = true;
                    } else{
                        a++;
                        hasil = false;
                        //cek(jawaban,ctr-1,map);
                    }
                }while(!hasil && a < jawaban[ctr-1].length());
            }
        }
        System.out.println("A: " +a);
        System.out.println("X : " +x);
        System.out.println("Y : " +y);
        System.out.println("CTR : " +ctr);
        System.out.println(hasil);
        System.out.println(jawaban[ctr]);
        return hasil;
    }
    
    public static void pemecah(String jawaban[], char map[][],int ctr){
        if(ctr == 5){
            ct(map);
        } else {           
            if(cek(jawaban,ctr,map)){
                if(ctr % 2 == 0){
                    for (int i = 1; i < jawaban[ctr].length(); i++) {
                        map[y][x+i] = jawaban[ctr].charAt(i);
                         
                    }
                }else if(ctr % 2 == 1){
                    for (int i = 1; i < jawaban[ctr].length(); i++) {
                       map[y+i][x] = jawaban[ctr].charAt(i);
                       
                    }
                }
          
               pemecah(jawaban,map,ctr+1);
            } else{
             //  pemecah(jawaban,map,ctr);
                //cek(jawaban, ctr, map);
               // pemecah(jawaban,map,ctr+1);
            }
        }
    }
    
    public static void main(String[] args) {
        String jawaban[] = new String[7];
        jawaban[0] = "katak";
        jawaban[1] = "anjing";
        jawaban[2] = "gajah";
        jawaban[3] = "jerapah";
        jawaban[4] = "elang";
        jawaban[5] = "ayam";
        jawaban[6] = "you";
        
        char[][] map = new char[50][50];        
        int ctr = 0;       
        isimap(map);
        pemecah(jawaban,map,ctr);
        
    }
    
}
