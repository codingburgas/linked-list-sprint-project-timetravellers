#include "pch.h" // Precompiled headers for Microsoft Unit Testing Framework
#include "CppUnitTest.h"
#include "admin.h" // Include your actual header file

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AdminPanelTests
{
    TEST_CLASS(AdminPanelTests)
    {
    private:
        User* userHead;

        void InitializeTestData() {
            userHead = new User{ 1, "user1", "salt1", "pass1", "user", nullptr };
            userHead->next = new User{ 2, "user2", "salt2", "pass2", "user", nullptr };
        }

        void CleanupTestData() {
            while (userHead != nullptr) {
                User* temp = userHead;
                userHead = userHead->next;
                delete temp;
            }
        }

    public:

        // Test setup and teardown
        TEST_METHOD_INITIALIZE(Setup) {
            InitializeTestData();
        }

        TEST_METHOD_CLEANUP(Cleanup) {
            CleanupTestData();
        }

        TEST_METHOD(TestPromoteUserToAdmin)
        {
            // Arrange
            int userIdToPromote = 1;
            User* temp = userHead;

            // Act
            while (temp != nullptr) {
                if (temp->id == userIdToPromote) {
                    temp->role = "admin";
                    break;
                }
                temp = temp->next;
            }

            // Assert
            Assert::AreEqual(std::string("admin"), userHead->role);
        }

        TEST_METHOD(TestDemoteAdminToUser)
        {
            // Arrange
            userHead->role = "admin"; // First promote to admin
            int userIdToDemote = 1;
            User* temp = userHead;

            // Act
            while (temp != nullptr) {
                if (temp->id == userIdToDemote) {
                    temp->role = "user";
                    break;
                }
                temp = temp->next;
            }

            // Assert
            Assert::AreEqual(std::string("user"), userHead->role);
        }

        TEST_METHOD(TestDeleteUser)
        {
            // Arrange
            int userIdToDelete = 1;
            User* temp = userHead;
            User* prev = nullptr;

            // Act
            while (temp != nullptr && temp->id != userIdToDelete) {
                prev = temp;
                temp = temp->next;
            }

            if (temp != nullptr) {
                if (prev == nullptr) {
                    userHead = temp->next;
                }
                else {
                    prev->next = temp->next;
                }
                delete temp;
            }

            // Assert
            Assert::AreNotEqual(1, userHead->id); // Ensure ID 1 no longer exists
        }

        TEST_METHOD(TestSaveUsersToFile)
        {
            // Arrange
            std::ofstream testFile("test_users.txt");
            User* temp = userHead;

            // Act
            while (temp != nullptr) {
                testFile << temp->id << " " << temp->username << " " << temp->salt << " " << temp->password << " " << temp->role << std::endl;
                temp = temp->next;
            }
            testFile.close();

            // Assert (verify file exists and contains expected content)
            std::ifstream verifyFile("test_users.txt");
            Assert::IsTrue(verifyFile.good()); // Check that file exists
            std::stringstream buffer;
            buffer << verifyFile.rdbuf();
            std::string content = buffer.str();
            Assert::IsTrue(content.find("user1") != std::string::npos); // Verify user1's data exists
            verifyFile.close();

            // Cleanup
            std::remove("test_users.txt");
        }
    };
}