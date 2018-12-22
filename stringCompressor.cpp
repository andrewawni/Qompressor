#include "stringCompressor.h"

string StringCompressor::decimalToBinaryString(int x, int nBits)
{
    //A function that converts a decimal value to a string of ASCII characters
    //that represent that value in base 2 (binary) of nBits in length
    string s;
    if (x == 0) //Odd zero case
    {
        while (s.size() != nBits)
            s.insert(s.begin(), '0');
        return s; //Returns a zero string of length nBits
    }

    while (x != 0) //Converts the decimal number to binary using the popular ÷2 method
    {
        s.insert(s.begin(), (char) ((x%2) + '0'));
        x /= 2;
    }

    while (s.size() != nBits) //Append zeroes at the left to make sure that the length is nBits
        s.insert(s.begin(), '0');

    return s;
}


int StringCompressor::binaryStringtoDecimal(string s)
{
    //A function that returns the decimal value of a binary string.
    int value{0};

    for (int i = 0; i < s.size(); i++)
        value += (int) ((pow(2, s.size()-(i+1))) * (s[i] - '0'));
    // Bit value * Weight of the bit

    return value;
}


string StringCompressor::binaryStreamtoASCII(string encodedString)
{
    //A function that exports the binary stream of instructions to a file
    string ASCIIString;
    string byteString; //Empty string to hold the stream

    int counter = 1; //Counter to count the number of bytes exported

    for (int i = 0; i < encodedString.size(); i++)
    {
        byteString += encodedString[i]; //Append the bit
        if (counter == 8 && i != encodedString.size() - 1) //If the byteString has 8 bits and it isn't the last byte
        {
            //cout << byteString << endl; //Kept temporarily for debugging
            int value = binaryStringtoDecimal(byteString); //Convert the binary byte to a decimal value
            ASCIIString.push_back((char) (value - 128)); //Cast the value - 128 to prevent overflowing into a character.
            byteString.clear(); //Clear the string
            counter = 0; // Reset the counter
        }

        else if (i == encodedString.size() - 1) //If this is the last byte
        {
            int ignore; //Variable to hold the number of ignored bytes depending on the
            /*
            Ignore is a value that is represented by a 3 bit binary substring at the end
            of the string. It tells the stream reader the number of bytes to ignore at the
            end.
            This is done because computers store files in bytes, so that's 8 bits minumum,
            so the length of the string has to be divisble by 8 in the end before exporting.
            If that isn't the default case, we append zeroes and the ignore value until the length
            of the binary stream becomes divisible by 8.
            */
            if (counter == 6) //If the byte's length is 6
            {
                ignore = 7; // Set ignore to 7
                for (int j = 0; j < 2 ; j++) // Append 2 zeroes to make the first byte equal 8 in length
                    byteString.push_back('0');
            }

            else if (counter == 7)
            {
                ignore = 6;
                byteString.push_back('0');
            }

            else if (counter == 8)	ignore = 5;

            else //If the length ranges from 0 to 5
            {
                ignore = 8 - (counter + 3);
                for (int j = 0; j < ignore ; j++)
                    byteString.push_back('0');
                byteString += decimalToBinaryString(ignore, 3); //Append the 3 bit ignore value
            }

            // << byteString << endl;
            int value = binaryStringtoDecimal(byteString); //Convert the binarystring to a decimal value
            ASCIIString.push_back((char) (value - 128)); //Export current byte
            byteString.clear();

            if (counter == 6 || counter == 7 || counter == 8)
            {
                //Extra case where we need to add an extra byte to make up for the length of
                //the last byte.
                for (int j = 0; j < 5; j++)
                    byteString.push_back('0');

                byteString += decimalToBinaryString(ignore, 3);
                //cout << byteString << endl;
                int value = binaryStringtoDecimal(byteString);
                ASCIIString.push_back((char) (value - 128));
                byteString.clear();
            }
        }

        counter++; //Incerement the counter;
    }
    return ASCIIString;
}



string StringCompressor::asciitoBinaryStream(string asciiString)
{
    string inputBinaryStream, binaryStream;

    inputBinaryStream = asciiString; //Read the whole ASCII String
//    std::cout << inputBinaryStream << std::endl;
    string instructions;
    for (int i = 0; i < inputBinaryStream.size(); i++)
    {
        //This loop converts the ASCII String to its original binary stream state
        instructions = decimalToBinaryString((int) (inputBinaryStream[i] + 128), 8);
        binaryStream += instructions;
    }
//    std::cout << binaryStream << std::endl;
    //cout << endl << "Read Binary Stream:\t" << binaryStream << endl; //Prints the read binary stream
    //e.g. the binary stream before the final bits are ignored.

    string bitsToIgnore; //Number of bits to ignore in binary
    for (int i = binaryStream.size() - 3; i < binaryStream.size(); i++)
        bitsToIgnore.push_back(binaryStream[i]); //Read it from the binary stream
    int numberOfBitstoIgnore = binaryStringtoDecimal(bitsToIgnore); //Convert to decimal
    //cout << "Ignored Bytes:\t " << numberOfBitstoIgnore << endl; //Print it
//    std::cout << binaryStream << std::endl;
    for (int i = 0; i < numberOfBitstoIgnore + 3; i++)
        binaryStream.pop_back(); //Delete the last nBits + the 3 bits that represent that ignore value

    //cout << "Actual Binary Stream:\t" << binaryStream; //Print the binary stream after being ignored.
    return binaryStream; //Return the new stream
}
