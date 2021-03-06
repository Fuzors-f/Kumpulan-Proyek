-- BARANG YANG BELUM LUNAS KE SUPPLIER
SELECT RPAD(LPAD(NOTA_BELI.ID_NOTA_BELI,10,' '),12,' ') "ID NOTA_BELI", RPAD(LPAD(NOTA_BELI.TANGGAL_NOTA_BELI,10,' '),15,' ') "TANGGAL BELI",SUPPLIER.NAMA_SUPPLIER "NAMA SUPPLIER", LPAD('031-' || SUPPLIER.NO_TELEPON_SUPPLIER,10,' ') "TELEPON", 
LPAD('Rp '|| SUM(NOTA_BELI_BARANG.HARGA_POKOK_BARANG),17,' ') "UTANG YANG KURANG", RPAD(LPAD(NOTA_BELI.TENGGANG_PEMBAYARAN,15,' '),20,' ')"TENGGANG PEMBAYARAN"
FROM NOTA_BELI, BARANG, NOTA_BELI_BARANG, SUPPLIER
WHERE SUPPLIER.ID_SUPPLIER = NOTA_BELI.ID_SUPPLIER AND NOTA_BELI.ID_NOTA_BELI = NOTA_BELI_BARANG.ID_NOTA_BELI  AND NOTA_BELI_BARANG.ID_BARANG = BARANG.ID_BARANG
AND NOTA_BELI.STATUS_PEMBAYARAN LIKE 'BELUM LUNAS'
GROUP BY NOTA_BELI.ID_NOTA_BELI,NOTA_BELI.TANGGAL_NOTA_BELI,SUPPLIER.NAMA_SUPPLIER, SUPPLIER.NO_TELEPON_SUPPLIER,NOTA_BELI.TENGGANG_PEMBAYARAN
ORDER BY NOTA_BELI.TANGGAL_NOTA_BELI ASC;

-- BANYAK BARANG YANG LAKU 

SELECT NOTA_JUAL.TANGGAL_NOTA_JUAL "TANGGAL JUAL",BARANG.ID_BARANG "ID_BARANG",BARANG.NAMA_BARANG "NAMA BARANG",NOTA_JUAL_BARANG.BANYAK_BARANG_TERJUAL "DIBELI"
FROM NOTA_JUAL,BARANG,NOTA_JUAL_BARANG
WHERE NOTA_JUAL.ID_NOTA_JUAL = NOTA_JUAL_BARANG.ID_NOTA_JUAL AND NOTA_JUAL_BARANG.ID_BARANG = BARANG.ID_BARANG
GROUP BY NOTA_JUAL.TANGGAL_NOTA_JUAL,BARANG.ID_BARANG,BARANG.NAMA_BARANG,NOTA_JUAL_BARANG.BANYAK_BARANG_TERJUAL
HAVING SUM(NOTA_JUAL_BARANG.BANYAK_BARANG_TERJUAL) > 10
ORDER BY NOTA_JUAL.TANGGAL_NOTA_JUAL;

-- BANYAK BARANG YANG GA LAKU 
SELECT NOTA_JUAL.TANGGAL_NOTA_JUAL "TANGGAL",BARANG.ID_BARANG "ID_BARANG",BARANG.NAMA_BARANG "NAMA BARANG",NOTA_JUAL_BARANG.BANYAK_BARANG_TERJUAL "DIBELI"
FROM NOTA_JUAL,BARANG,NOTA_JUAL_BARANG
WHERE NOTA_JUAL.ID_NOTA_JUAL = NOTA_JUAL_BARANG.ID_NOTA_JUAL AND NOTA_JUAL_BARANG.ID_BARANG = BARANG.ID_BARANG
GROUP BY NOTA_JUAL.TANGGAL_NOTA_JUAL,BARANG.ID_BARANG,BARANG.NAMA_BARANG,NOTA_JUAL_BARANG.BANYAK_BARANG_TERJUAL
HAVING NOTA_JUAL_BARANG.BANYAK_BARANG_TERJUAL < 10
ORDER BY NOTA_JUAL.TANGGAL_NOTA_JUAL;

--BARANG YANG HARUS RE-STOK 
SELECT RPAD(BARANG.NAMA_BARANG,15,' ') "NAMA BARANG", SUPPLIER.NAMA_SUPPLIER "NAMA SUPPLIER",RPAD('031-' || SUPPLIER.NO_TELEPON_SUPPLIER,10,' ') "NO_TELEPON",BARANG.STOK_BARANG-SUM(NOTA_JUAL_BARANG.BANYAK_BARANG_TERJUAL) "SISA", BARANG.MINIMAL_STOK "MINIMAL STOK"
FROM BARANG,SUPPLIER,NOTA_JUAL_BARANG,NOTA_BELI,NOTA_BELI_BARANG
WHERE SUPPLIER.ID_SUPPLIER = NOTA_BELI.ID_SUPPLIER AND NOTA_BELI.ID_NOTA_BELI = NOTA_BELI_BARANG.ID_NOTA_BELI AND NOTA_BELI_BARANG.ID_BARANG = BARANG.ID_BARANG
AND BARANG.ID_BARANG = NOTA_JUAL_BARANG.ID_BARANG AND BARANG.MINIMAL_STOK > 0 
HAVING BARANG.STOK_BARANG-SUM(NOTA_JUAL_BARANG.BANYAK_BARANG_TERJUAL) < BARANG.MINIMAL_STOK
GROUP BY BARANG.NAMA_BARANG,SUPPLIER.NAMA_SUPPLIER,SUPPLIER.NO_TELEPON_SUPPLIER,BARANG.STOK_BARANG,NOTA_JUAL_BARANG.BANYAK_BARANG_TERJUAL,BARANG.MINIMAL_STOK;