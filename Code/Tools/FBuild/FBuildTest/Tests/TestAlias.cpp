// TestAlias.cpp
//------------------------------------------------------------------------------

// Includes
//------------------------------------------------------------------------------
#include "FBuildTest.h"

#include "Tools/FBuild/FBuildCore/FBuild.h"
#include "Tools/FBuild/FBuildCore/BFF/BFFParser.h"
#include "Tools/FBuild/FBuildCore/BFF/Functions/Function.h"

#include "Core/Strings/AStackString.h"

// TestAlias
//------------------------------------------------------------------------------
class TestAlias : public FBuildTest
{
private:
    DECLARE_TESTS

    // Tests
    void MissingAliasTarget() const;
    void ReflectionAliasResolution() const;
    void NonFileNodes() const;
};

// Register Tests
//------------------------------------------------------------------------------
REGISTER_TESTS_BEGIN( TestAlias )
    REGISTER_TEST( MissingAliasTarget )
    REGISTER_TEST( ReflectionAliasResolution )
    REGISTER_TEST( NonFileNodes )
REGISTER_TESTS_END

// MissingAliasTarget
//------------------------------------------------------------------------------
void TestAlias::MissingAliasTarget() const
{
    FBuildTestOptions options;
    options.m_ConfigFile = "Tools/FBuild/FBuildTest/Data/TestAlias/alias.bff";
    options.m_ForceCleanBuild = true;

    // Parsing of BFF should be ok
    FBuild fBuild( options );
    TEST_ASSERT( fBuild.Initialize() );

    // building should fail
    TEST_ASSERT( fBuild.Build( "alias" ) == false );
}

// ReflectionAliasResolution
//------------------------------------------------------------------------------
void TestAlias::ReflectionAliasResolution() const
{
    // FAIL Case 1: An Alias to >1 item
    {
        FBuildTestOptions options;
        options.m_ConfigFile = "Tools/FBuild/FBuildTest/Data/TestAlias/Reflection/bad_string.bff";

        // Parsing of BFF should FAIL
        FBuild fBuild( options );
        TEST_ASSERT( fBuild.Initialize() == false );
    }

    // FAIL Case 2: An Alias to >1 item (indirectly via another alias)
    {
        FBuildTestOptions options;
        options.m_ConfigFile = "Tools/FBuild/FBuildTest/Data/TestAlias/Reflection/bad_string_recurse.bff";

        // Parsing of BFF should FAIL
        FBuild fBuild( options );
        TEST_ASSERT( fBuild.Initialize() == false );
    }

    // OK Case 1: An alias to single item
    {
        FBuildTestOptions options;
        options.m_ConfigFile = "Tools/FBuild/FBuildTest/Data/TestAlias/Reflection/ok_string.bff";

        // Parsing of BFF should FAIL
        FBuild fBuild( options );
        TEST_ASSERT( fBuild.Initialize() );
    }

    // OK Case 2: An alias to single item (indirectly via another alias)
    {
        FBuildTestOptions options;
        options.m_ConfigFile = "Tools/FBuild/FBuildTest/Data/TestAlias/Reflection/ok_string_recurse.bff";

        // Parsing of BFF should FAIL
        FBuild fBuild( options );
        TEST_ASSERT( fBuild.Initialize() );
    }
}

// NonFileNodes
//------------------------------------------------------------------------------
void TestAlias::NonFileNodes() const
{
    FBuildTestOptions options;
    options.m_ConfigFile = "Tools/FBuild/FBuildTest/Data/TestAlias/Reflection/ok_to_non_filenode.bff";
    FBuild fBuild( options );
    TEST_ASSERT( fBuild.Initialize() );
}

//------------------------------------------------------------------------------
