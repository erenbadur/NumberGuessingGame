// Created by Eren Badur

#include <iostream>
#include "feedback.h"

using namespace std;

struct node     // The node structure for the linked lists is created.
{
    int digit;
    node * next;
};


bool checkInput(string &guess)  // Checks if the input is in correct format.
{
    if(guess.length() != 3)     // guess should contain three digits
    {
        return false;
    }

    else if(guess.find_first_not_of("0123456789") != string::npos)  // guess should only contain digits.
    {
        return false;
    }

    else if(guess[0] == guess[1] || guess[0] == guess[2] || guess[1] == guess[2])   // Each digit should be unique.
    {
        return false;
    }

    return true;
}

bool search(node * head, int val)   // Checks if a digit is in the linked list specified.
{
    node * currentNode = head;

    while(currentNode != nullptr)   // Traverse the linked list.
    {
        if(currentNode->digit == val)
        {
            return true;
        }

        currentNode = currentNode->next;    // Move to the next node.
    }

    return false;
}

// Begin: code taken from ptrfunc.cpp and updated
node * addToList(node * head, int newVal)   // Adds a new element to the linked list specified.
{
    if(search(head, newVal))    // Checks if the new element is already in the list.
    {
        return head;
    }

    node * newNode = new node;
    newNode->digit = newVal;
    newNode->next = nullptr;

    if(head == nullptr)     // Checks if the list is empty.
    {
        return newNode;
    }

    if(head->digit > newVal)    // Checks if the new element is smaller than the other elements starting from the head.
    {
        newNode->next = head;
        return newNode;
    }

    node * temp = head;
    while(temp->next != nullptr && temp->next->digit < newVal)
    {
        temp = temp->next;
    }

    newNode->next = temp->next;
    temp->next = newNode;
    return head;
}
// End: code taken from ptrfunc.cpp and updated

node * deleteNode(node * head, int value)
{
    node * temp = head;
    node * preNode = nullptr;

    while(temp != nullptr)
    {
        if(temp->digit == value)
        {
            if(preNode == nullptr)
            {
                head = temp->next;
                delete temp;
            }

            else
            {
                preNode->next = temp->next;
                delete temp;
            }

            return head;
        }

        preNode = temp;
        temp = temp->next;
    }

    return head;
}

int getCount(node * head)   // Counts the number of elements in the linked list specified.
{
    int count = 0;
    node * currNode = head;
    while(currNode != nullptr)
    {
        count++;
        currNode = currNode->next;
    }
    return count;
}

void printList(node * head)     // Prints the desired linked list.
{
    node * ptr = head;
    while(ptr != nullptr)
    {
        std::cout << ptr->digit << " ";
        ptr = ptr->next;
    }
}

int main()
{
    node * s1_i_head = nullptr; // Empty linked list for slot1 impossible digits is created
    node * s1_p_head = nullptr; // Empty linked list for slot1 possible digits is created
    node * s2_i_head = nullptr; // Empty linked list for slot2 impossible digits is created
    node * s2_p_head = nullptr; // Empty linked list for slot2 possible digits is created
    node * s3_i_head = nullptr; // Empty linked list for slot3 impossible digits is created
    node * s3_p_head = nullptr; // Empty linked list for slot3 possible digits is created

    node * impossibles[3] = {s1_i_head, s1_i_head, s2_i_head}; // Array for impossible pointers
    node * possibles[3] = {s1_p_head, s2_p_head, s3_p_head}; // Array for possible pointers

    int game_id;    // game_id is taken as the user input.
    cout << "Please enter a game ID." << endl;
    cin >> game_id;

    string guess;   // guess is taken as the user input.
    while(get_the_feedback(guess, game_id) != "GGG")
    {
        cout << "Enter your guess." << endl;
        cin >> guess;

        if(!checkInput(guess))  // Asks until it gets a valid guess.
        {
            cout << "Invalid guess. ";
        }

        else    // Continues after a valid input is entered.
        {
            if(get_the_feedback(guess, game_id)[0] == 'R')  // If slot1 is Red.
            {
                s1_i_head = addToList(s1_i_head, int(guess[0]) - 48); // Adds the digit in slot1 of guess to s1_i_head.
                s2_i_head = addToList(s2_i_head, int(guess[0]) - 48); // Adds the digit in slot1 of guess to s2_i_head.
                s3_i_head = addToList(s3_i_head, int(guess[0]) - 48); // Adds the digit in slot1 of guess to s3_i_head.
            }

            else if(get_the_feedback(guess, game_id)[0] == 'Y') // If slot1 is Yellow.
            {
                s1_p_head = deleteNode(s1_p_head, int(guess[0]) - 48); // Deletes the digit in slot1 of guess from s1_p_head.
                s1_i_head = addToList(s1_i_head, int(guess[0]) - 48); // Adds the digit in slot1 of guess to s1_i_head.

                if( (get_the_feedback(guess, game_id)[0] == 'Y') && (get_the_feedback(guess, game_id)[1] == 'Y') && (get_the_feedback(guess, game_id)[2] == 'Y') )
                {
                    s2_p_head = deleteNode(s2_p_head, int(guess[1]) - 48); // Deletes the digit in slot1 of guess from s2_p_head.
                    s2_i_head = addToList(s2_i_head, int(guess[1]) - 48); // Adds the digit in slot1 of guess to s2_i_head.
                    s3_p_head = deleteNode(s3_p_head, int(guess[2]) - 48); // Deletes the digit in slot2 of guess from s3_p_head.
                    s3_i_head = addToList(s3_i_head, int(guess[2]) - 48); // Adds the digit in slot2 of guess to s3_i_head.

                    if(!search(s2_i_head, int(guess[0]) - 48)) // Adds slot1 value to s2_p_head if it is not in s2_i_head.
                    {
                        s2_p_head = addToList(s2_p_head, int(guess[0]) - 48);
                    }

                    if(!search(s3_i_head, int(guess[0]) - 48)) // Adds slot1 value to s3_p_head if it is not in s3_i_head.
                    {
                        s3_p_head = addToList(s3_p_head, int(guess[0]) - 48);
                    }

                    if(!search(s1_i_head, int(guess[1]) - 48)) // Adds slot2 value to s1_p_head if it is not in s1_i_head.
                    {
                        s1_p_head = addToList(s1_p_head, int(guess[1]) - 48);
                    }

                    if(!search(s3_i_head, int(guess[1]) - 48)) // Adds slot2 value to s3_p_head if it is not in s3_i_head.
                    {
                        s3_p_head = addToList(s3_p_head, int(guess[1]) - 48);
                    }

                    if(!search(s1_i_head, int(guess[2]) - 48)) // Adds slot3 value to s1_p_head if it is not in s1_i_head.
                    {
                        s1_p_head = addToList(s1_p_head, int(guess[2]) - 48);
                    }

                    if(!search(s2_i_head, int(guess[2]) - 48)) // Adds slot3 value to s2_p_head if it is not in s2_i_head.
                    {
                        s2_p_head = addToList(s2_p_head, int(guess[2]) - 48);
                    }
                }

                else
                {
                    if(get_the_feedback(guess, game_id)[1] == 'Y')  // If also slot2 is Yellow.
                    {
                        if(!search(s2_i_head, int(guess[0]) - 48)) // Adds slot1 value to s2_p_head if it is not in s2_i_head.
                        {
                            s2_p_head = addToList(s2_p_head, int(guess[0]) - 48);
                        }

                        if(!search(s3_i_head, int(guess[0]) - 48)) // Adds slot1 value to s3_p_head if it is not in s3_i_head.
                        {
                            s3_p_head = addToList(s3_p_head, int(guess[0]) - 48);
                        }

                        if(!search(s1_i_head, int(guess[1]) - 48)) // Adds slot2 value to s1_p_head if it is not in s1_i_head.
                        {
                            s1_p_head = addToList(s1_p_head, int(guess[1]) - 48);
                        }

                        if(!search(s3_i_head, int(guess[1]) - 48)) // Adds slot2 value to s3_p_head if it is not in s3_i_head.
                        {
                            s3_p_head = addToList(s3_p_head, int(guess[1]) - 48);
                        }
                    }

                    else if(get_the_feedback(guess, game_id)[2] == 'Y') // If also slot 3 is Yellow.
                    {
                        if(!search(s2_i_head, int(guess[0]) - 48))
                        {
                            s2_p_head = addToList(s2_p_head, int(guess[0]) - 48);
                        }

                        if(!search(s3_i_head, int(guess[0]) - 48))
                        {
                            s3_p_head = addToList(s3_p_head, int(guess[0]) - 48);
                        }

                        if(!search(s1_i_head, int(guess[2]) - 48))
                        {
                            s1_p_head = addToList(s1_p_head, int(guess[2]) - 48);
                        }

                        if(!search(s2_i_head, int(guess[2]) - 48))
                        {
                            s2_p_head = addToList(s2_p_head, int(guess[2]) - 48);
                        }
                    }

                    else    // If slot1 is the only Yellow.
                    {
                        if(!search(s2_i_head, int(guess[0]) - 48))
                        {
                            s2_p_head = addToList(s2_p_head, int(guess[0]) - 48);
                        }
                        if(!search(s3_i_head, int(guess[0]) - 48))
                        {
                            s3_p_head = addToList(s3_p_head, int(guess[0]) - 48);
                        }
                    }
                }
            }

            else if(get_the_feedback(guess, game_id)[0] == 'G') // If slot1 is Green.
            {
                s1_p_head = addToList(s1_p_head, int(guess[0]) - 48);
                s2_i_head = addToList(s2_i_head, int(guess[0]) - 48);
                s3_i_head = addToList(s3_i_head, int(guess[0]) - 48);
                s2_p_head = deleteNode(s2_p_head, int(guess[0]) - 48);
                s3_p_head = deleteNode(s3_p_head, int(guess[0]) - 48);

                for(int i = 0; i <= 9; i++)
                {
                    if(i == 0)
                    {
                        if(i != int(guess[0]) - 48)
                        {
                            s1_i_head = addToList(s1_i_head, i);
                        }
                    }

                    else
                    {
                        if(i != int(guess[0]) - 48 && !search(s1_p_head, i))
                        {
                            s1_i_head = addToList(s1_i_head, i);
                        }
                    }
                }
            }


            if(get_the_feedback(guess, game_id)[1] == 'R')  // If slot2 is Red.
            {
                s1_i_head = addToList(s1_i_head, int(guess[1]) - 48);
                s2_i_head = addToList(s2_i_head, int(guess[1]) - 48);
                s3_i_head = addToList(s3_i_head, int(guess[1]) - 48);
            }

            else if(get_the_feedback(guess, game_id)[1] == 'Y') // If slot2 is Yellow.
            {
                s2_p_head = deleteNode(s2_p_head, int(guess[1]) - 48);
                s2_i_head = addToList(s2_i_head, int(guess[1]) - 48);

                if( (get_the_feedback(guess, game_id)[0] == 'Y') && (get_the_feedback(guess, game_id)[1] == 'Y') && (get_the_feedback(guess, game_id)[2] == 'Y') )
                {
                    s1_p_head = deleteNode(s1_p_head, int(guess[0]) - 48);
                    s1_i_head = addToList(s1_i_head, int(guess[0]) - 48);
                    s3_p_head = deleteNode(s3_p_head, int(guess[2]) - 48);
                    s3_i_head = addToList(s3_i_head, int(guess[2]) - 48);

                    if(!search(s2_i_head, int(guess[0]) - 48)) // Adds slot1 value to s2_p_head if it is not in s2_i_head.
                    {
                        s2_p_head = addToList(s2_p_head, int(guess[0]) - 48);
                    }

                    if(!search(s3_i_head, int(guess[0]) - 48)) // Adds slot1 value to s3_p_head if it is not in s3_i_head.
                    {
                        s3_p_head = addToList(s3_p_head, int(guess[0]) - 48);
                    }

                    if(!search(s1_i_head, int(guess[1]) - 48)) // Adds slot2 value to s1_p_head if it is not in s1_i_head.
                    {
                        s1_p_head = addToList(s1_p_head, int(guess[1]) - 48);
                    }

                    if(!search(s3_i_head, int(guess[1]) - 48)) // Adds slot2 value to s3_p_head if it is not in s3_i_head.
                    {
                        s3_p_head = addToList(s3_p_head, int(guess[1]) - 48);
                    }

                    if(!search(s1_i_head, int(guess[2]) - 48)) // Adds slot3 value to s1_p_head if it is not in s1_i_head.
                    {
                        s1_p_head = addToList(s1_p_head, int(guess[2]) - 48);
                    }

                    if(!search(s2_i_head, int(guess[2]) - 48)) // Adds slot3 value to s2_p_head if it is not in s2_i_head.
                    {
                        s2_p_head = addToList(s2_p_head, int(guess[2]) - 48);
                    }
                }

                else
                {
                    if(get_the_feedback(guess, game_id)[0] == 'Y')  // If also slot1 is Yellow.
                    {
                        if(!search(s1_i_head, int(guess[1]) - 48))
                        {
                            s1_p_head = addToList(s1_p_head, int(guess[1]) - 48);
                        }

                        if(!search(s3_i_head, int(guess[1]) - 48))
                        {
                            s3_p_head = addToList(s3_p_head, int(guess[1]) - 48);
                        }

                        if(!search(s2_i_head, int(guess[0]) - 48))
                        {
                            s2_p_head = addToList(s2_p_head, int(guess[0]) - 48);
                        }

                        if(!search(s3_i_head, int(guess[0]) - 48))
                        {
                            s3_p_head = addToList(s3_p_head, int(guess[0]) - 48);
                        }
                    }

                    else if(get_the_feedback(guess, game_id)[2] == 'Y') // If also slot3 is Yellow.
                    {
                        if(!search(s1_i_head, int(guess[1]) - 48))
                        {
                            s1_p_head = addToList(s1_p_head, int(guess[1]) - 48);
                        }

                        if(!search(s3_i_head, int(guess[1]) - 48))
                        {
                            s3_p_head = addToList(s3_p_head, int(guess[1]) - 48);
                        }

                        if(!search(s1_i_head, int(guess[2]) - 48))
                        {
                            s1_p_head = addToList(s1_p_head, int(guess[2]) - 48);
                        }

                        if(!search(s2_i_head, int(guess[2]) - 48))
                        {
                            s2_p_head = addToList(s2_p_head, int(guess[2]) - 48);
                        }
                    }

                    else    // If slot2 is the only Yellow.
                    {
                        if(!search(s1_i_head, int(guess[1]) - 48))
                        {
                            s1_p_head = addToList(s1_p_head, int(guess[1]) - 48);
                        }

                        if(!search(s3_i_head, int(guess[1]) - 48))
                        {
                            s3_p_head = addToList(s3_p_head, int(guess[1]) - 48);
                        }
                    }
                }
            }

            else if(get_the_feedback(guess, game_id)[1] == 'G') // If slot2 is Green.
            {
                s2_p_head = addToList(s2_p_head, int(guess[1]) - 48);
                s1_i_head = addToList(s1_i_head, int(guess[1]) - 48);
                s3_i_head = addToList(s3_i_head, int(guess[1]) - 48);
                s1_p_head = deleteNode(s1_p_head, int(guess[1]) - 48);
                s3_p_head = deleteNode(s3_p_head, int(guess[1]) - 48);

                for(int i = 0; i <= 9; i++)
                {
                    if(i == 0)
                    {
                        if(i != int(guess[1]) - 48)
                        {
                            s2_i_head = addToList(s2_i_head, i);
                        }
                    }

                    else
                    {
                        if(i != int(guess[1]) - 48 && !search(s2_p_head, i))
                        {
                            s2_i_head = addToList(s2_i_head, i);
                        }
                    }
                }
            }


            if(get_the_feedback(guess, game_id)[2] == 'R')  // If slot3 is Red.
            {
                s1_i_head = addToList(s1_i_head, int(guess[2]) - 48);
                s2_i_head = addToList(s2_i_head, int(guess[2]) - 48);
                s3_i_head = addToList(s3_i_head, int(guess[2]) - 48);
            }

            else if(get_the_feedback(guess, game_id)[2] == 'Y') // If slot3 is Yellow.
            {
                s3_p_head = deleteNode(s3_p_head, int(guess[2]) - 48);
                s3_i_head = addToList(s3_i_head, int(guess[2]) - 48);

                if( (get_the_feedback(guess, game_id)[0] == 'Y') && (get_the_feedback(guess, game_id)[1] == 'Y') && (get_the_feedback(guess, game_id)[2] == 'Y') )
                {
                    s1_p_head = deleteNode(s1_p_head, int(guess[0]) - 48);
                    s1_i_head = addToList(s1_i_head, int(guess[0]) - 48);
                    s2_p_head = deleteNode(s2_p_head, int(guess[1]) - 48);
                    s2_i_head = addToList(s2_i_head, int(guess[1]) - 48);


                    if(!search(s2_i_head, int(guess[0]) - 48)) // Adds slot1 value to s2_p_head if it is not in s2_i_head.
                    {
                        s2_p_head = addToList(s2_p_head, int(guess[0]) - 48);
                    }

                    if(!search(s3_i_head, int(guess[0]) - 48)) // Adds slot1 value to s3_p_head if it is not in s3_i_head.
                    {
                        s3_p_head = addToList(s3_p_head, int(guess[0]) - 48);
                    }

                    if(!search(s1_i_head, int(guess[1]) - 48)) // Adds slot2 value to s1_p_head if it is not in s1_i_head.
                    {
                        s1_p_head = addToList(s1_p_head, int(guess[1]) - 48);
                    }

                    if(!search(s3_i_head, int(guess[1]) - 48)) // Adds slot2 value to s3_p_head if it is not in s3_i_head.
                    {
                        s3_p_head = addToList(s3_p_head, int(guess[1]) - 48);
                    }

                    if(!search(s1_i_head, int(guess[2]) - 48)) // Adds slot3 value to s1_p_head if it is not in s1_i_head.
                    {
                        s1_p_head = addToList(s1_p_head, int(guess[2]) - 48);
                    }

                    if(!search(s2_i_head, int(guess[2]) - 48)) // Adds slot3 value to s2_p_head if it is not in s2_i_head.
                    {
                        s2_p_head = addToList(s2_p_head, int(guess[2]) - 48);
                    }
                }

                else
                {
                    if(get_the_feedback(guess, game_id)[0] == 'Y') // If also slot1 is Yellow.
                    {
                        if(!search(s1_i_head, int(guess[2]) - 48))
                        {
                            s1_p_head = addToList(s1_p_head, int(guess[2]) - 48);
                        }

                        if(!search(s2_i_head, int(guess[2]) - 48))
                        {
                            s2_p_head = addToList(s2_p_head, int(guess[2]) - 48);
                        }

                        if(!search(s2_i_head, int(guess[0]) - 48))
                        {
                            s2_p_head = addToList(s2_p_head, int(guess[0]) - 48);
                        }

                        if(!search(s3_i_head, int(guess[0]) - 48))
                        {
                            s3_p_head = addToList(s3_p_head, int(guess[0]) - 48);
                        }
                    }

                    else if(get_the_feedback(guess, game_id)[1] == 'Y') // If also slot2 is Yellow.
                    {
                        if(!search(s1_i_head, int(guess[2]) - 48))
                        {
                            s1_p_head = addToList(s1_p_head, int(guess[2]) - 48);
                        }

                        if(!search(s2_i_head, int(guess[2]) - 48))
                        {
                            s2_p_head = addToList(s2_p_head, int(guess[2]) - 48);
                        }

                        if(!search(s1_i_head, int(guess[1]) - 48))
                        {
                            s1_p_head = addToList(s1_p_head, int(guess[1]) - 48);
                        }

                        if(!search(s3_i_head, int(guess[1]) - 48))
                        {
                            s3_p_head = addToList(s3_p_head, int(guess[1]) - 48);
                        }
                    }
                    else    // If slot3 is the only Yellow.
                    {
                        if(!search(s1_i_head, int(guess[2]) - 48))
                        {
                            s1_p_head = addToList(s1_p_head, int(guess[2]) - 48);
                        }

                        if(!search(s2_i_head, int(guess[2]) - 48))
                        {
                            s2_p_head = addToList(s2_p_head, int(guess[2]) - 48);
                        }
                    }
                }


            }

            else if(get_the_feedback(guess, game_id)[2] == 'G') // If slot3 is Green.
            {
                s3_p_head = addToList(s3_p_head, int(guess[2]) - 48);
                s1_i_head = addToList(s1_i_head, int(guess[2]) - 48);
                s2_i_head = addToList(s2_i_head, int(guess[2]) - 48);
                s1_p_head = deleteNode(s1_p_head, int(guess[2]) - 48);
                s2_p_head = deleteNode(s2_p_head, int(guess[2]) - 48);

                for(int i = 0; i <= 9; i++)
                {
                    if(i == 0)
                    {
                        if(i != int(guess[2]) - 48)
                        {
                            s3_i_head = addToList(s3_i_head, i);
                        }
                    }

                    else
                    {
                        if(i != int(guess[2]) - 48 && !search(s3_p_head, i))
                        {
                            s3_i_head = addToList(s3_i_head, i);
                        }
                    }
                }
            }

            cout << "Linked lists: " << endl;

            cout << "Slot: 1" << endl;
            cout << "Impossibles: ";
            printList(s1_i_head);
            cout << endl;
            cout << "Possibles: ";
            printList(s1_p_head);
            cout << "\n" << endl;

            cout << "Slot: 2" << endl;
            cout << "Impossibles: ";
            printList(s2_i_head);
            cout << endl;
            cout << "Possibles: ";
            printList(s2_p_head);
            cout << "\n" << endl;

            cout << "Slot: 3" << endl;
            cout << "Impossibles: ";
            printList(s3_i_head);
            cout << endl;
            cout << "Possibles: ";
            printList(s3_p_head);
            cout << "\n" << endl;

            // If the guess is the same as the secret number or every impossible list contains 9 digits.
            if(get_the_feedback(guess, game_id) == "GGG" || ( getCount(s1_i_head) == 9 && getCount(s2_i_head) == 9 && getCount(s3_i_head) == 9) )
            {
                string secretNum = "";

                if(get_the_feedback(guess, game_id) == "GGG")
                {
                    for(int i = 0; i <= 9; i++)
                    {
                        if(search(s1_p_head, i))
                        {
                            string str_i = to_string(i);
                            secretNum += str_i;
                        }
                    }

                    for(int i = 0; i <= 9; i++)
                    {
                        if(search(s2_p_head, i))
                        {
                            string str_i = to_string(i);
                            secretNum += str_i;
                        }
                    }

                    for(int i = 0; i <= 9; i++)
                    {
                        if(search(s3_p_head, i))
                        {
                            string str_i = to_string(i);
                            secretNum += str_i;
                        }
                    }
                }
                else
                {
                    for(int i = 0; i <= 9; i++)
                    {
                        if(!search(s1_i_head, i))
                        {
                            string str_i = to_string(i);
                            secretNum += str_i;
                        }
                    }

                    for(int i = 0; i <= 9; i++)
                    {
                        if(!search(s2_i_head, i))
                        {
                            string str_i = to_string(i);
                            secretNum += str_i;
                        }
                    }

                    for(int i = 0; i <= 9; i++)
                    {
                        if(!search(s3_i_head, i))
                        {
                            string str_i = to_string(i);
                            secretNum += str_i;
                        }
                    }
                }

                cout << "The secret number is: " << secretNum << endl;
                cout << "Congrats! Now, deleting the lists..." << endl;

                for(int i = 0; i < 3; i++)
                {
                    delete(impossibles[i]);
                    impossibles[i] = nullptr;
                    delete(possibles[i]);
                    possibles[i] = nullptr;
                }

                return 0;
            }
        }
    }
}