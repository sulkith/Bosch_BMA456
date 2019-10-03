g++ Bosch_BMA456_config_file.cpp main.cpp -o directAccess
g++ Bosch_BMA456_config_file.cpp main_compressed.cpp -o compressed
./directAccess > directAccess_result.txt
./compressed > compressed_result.txt
diff compressed_result.txt directAccess_result.txt > differences.txt
