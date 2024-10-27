#!/bin/sh
echo "Test 1..."
g++ -pedantic -Wall -Wextra -std=c++17 -o 01_PushPopEmptySize 01_PushPopEmptySize.cpp
./01_PushPopEmptySize > 01_PushPopEmptySize.txt
diff 01_PushPopEmptySize_output.txt 01_PushPopEmptySize.txt

echo "Test 2..."
g++ -pedantic -Wall -Wextra -std=c++17 -o 02_FirstLast 02_FirstLast.cpp
./02_FirstLast > 02_FirstLast.txt
diff 02_FirstLast_output.txt 02_FirstLast.txt

echo "Test 3..."
g++ -pedantic -Wall -Wextra -std=c++17 -o 03_ClearContains 03_ClearContains.cpp
./03_ClearContains > 03_ClearContains.txt
diff 03_ClearContains_output.txt 03_ClearContains.txt

echo "Test 4..."
g++ -pedantic -Wall -Wextra -std=c++17 -o 04_CompareOperators 04_CompareOperators.cpp
./04_CompareOperators > 04_CompareOperators.txt
diff 04_CompareOperators_output.txt 04_CompareOperators.txt

echo "Test 5..."
g++ -pedantic -Wall -Wextra -std=c++17 -o 05_ConstructorsAndCopies 05_ConstructorsAndCopies.cpp
./05_ConstructorsAndCopies > 05_ConstructorsAndCopies.txt
diff 05_ConstructorsAndCopies_output.txt 05_ConstructorsAndCopies.txt

echo "Test 6..."
g++ -pedantic -Wall -Wextra -std=c++17 -o 06_DeepCopy 06_DeepCopy.cpp
./06_DeepCopy > 06_DeepCopy.txt
diff 06_DeepCopy_output.txt 06_DeepCopy.txt

echo "Test 7..."
g++ -pedantic -Wall -Wextra -std=c++17 -o 07_Apply 07_Apply.cpp
./07_Apply > 07_Apply.txt
diff 07_Apply_output.txt 07_Apply.txt

echo "Test 8..."
g++ -pedantic -Wall -Wextra -std=c++17 -o 08_RemoveWhere 08_RemoveWhere.cpp
./08_RemoveWhere > 08_RemoveWhere.txt
diff 08_RemoveWhere_output.txt 08_RemoveWhere.txt

echo "Test 9..."
g++ -pedantic -Wall -Wextra -std=c++17 -o 09_Transform 09_Transform.cpp
./09_Transform > 09_Transform.txt
diff 09_Transform_output.txt 09_Transform.txt

echo "Test 10..."
g++ -pedantic -Wall -Wextra -std=c++17 -o 10_ListOfLists 10_ListOfLists.cpp
./10_ListOfLists > 10_ListOfLists.txt
diff 10_ListOfLists_output.txt 10_ListOfLists.txt