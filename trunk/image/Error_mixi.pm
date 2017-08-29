#! /usr/bin/perl -w
# 2015-08-29  William A. Hudson

# Error handling mix-in functions.
#
# This is a "mix-in" module, meaning the exported functions become methods
# of the package in which they are imported.
#
# See EXPORT list for provided methods.
#
#---------------------------------------------------------------------------

package Error_mixi;

require Exporter;
@ISA       = qw( Exporter );
@EXPORT    = (
    'Error',		# Error message reporting.
    'die_Error',	# Die with error message.
    'carp_Error',	# Carp Error message.
);
@EXPORT_OK = (
);

use strict;


# Required object data:
# {
#    Error_sub    => sub {},	# Error message reporting subroutine.
#    Error_cnt    => 0,		# Number of errors reported.
#
# }


# Class data structure {ClassData}.  (private)
#    Do not change the pointer, as it may be copied into objects.
#    Use get_ClassData() for access by package name.
#    Object methods should use accessors to support inheritance.
#    Valid parameters are defined here, may be undef.
#
our $_ClassData = {
#?  Error_sub    => sub { warn( "ERROR:  ", @_ ) },	# global error sub
    TESTMODE     => undef,	# disable
};

#!! Possibly class data Error_sub could be default if none defined in the
# object.


#---------------------------------------------------------------------------
## Class data access.  (public)
#---------------------------------------------------------------------------
# Class data is strait forward, except when supporting object inheritance.
# For inheritance, either:
# A.  Put a reference to class data in each object.  OR
# B.  Object methods use accessors that are redefined in the new class.
# We are using B. here.


# Get class data structure.  (public)
#    This method must be redefined in each inheriting class so the $_ClassData
#    variable is private to each class.
#    Is a class method to reserve future capability.
# call:
#    $package->get_ClassData()		# Class method call only.
# return:
#    ()  = class data structure, hash reference
# external:
#    $_ClassData  = Class data structure reference in this package.
#
sub get_ClassData
{
#   my( $pkg ) = @_;
    return( $_ClassData );
}


# Initialize class data.  (public)
#    Use to initialize content of the class data structure.
#    Generally is called once before any functions are used, but may be
#        called again to reset class data.
#    Arguments are validated against predefined structure keys.
#    Note:  Class methods cannot use the object error callback, so the
#        return status should be explicitly checked.
# call:
#    $package->Init_class( key => value, .. )	# Class method call only.
# return:
#    ()  = class data structure, undef if errors
#
sub Init_class
{
    my( $pkg, %arg ) = @_;

    my $ok = 1;
    my $cx = $pkg->get_ClassData();

    while ( my( $key, $value ) = each( %arg ) )
    {
	if ( exists( $cx->{$key} ) ) {	# predefined in class structure
	    $cx->{$key} = $value;
	}
	else {
	    warn( "Error:  $pkg->Init_class():  unexpected argument:  '$key'\n" );
	    $ok = 0;
	}
    }

    return( ( $ok ) ? $cx : undef );
}


#---------------------------------------------------------------------------
## Error handling
#---------------------------------------------------------------------------
# The idea is to have all objects use a commone Error() sub.
# Each object gets just its Error_cnt incremented, plus the top-level
# Error_cnt based on what is put in this Class data.

# Error message reporting.
#    Call with no arguments to get the object error count.
# call:
#    $self->Error( @text )	Print error message, increment error count.
#    $self->Error()		Get object error count.
#    @text  = error message text, same as warn().
# return:
#    ()  = Error count, false if no errors are recorded in the object.
#
sub Error
{
    my $self = shift();

    if ( @_ ) {
	$self->{Error_cnt} ++;
	$self->{Error_sub}->( @_ );
    }
    return( $self->{Error_cnt} );
}


# Die with error message.
# call:
#    $self->die_Error( @text )
#    @text  = error message text, same as warn().
# return:
#    Never returns.
sub die_Error
{
    my( $self, @text ) = @_;

    $self->Error( @text );

    $! = 1;		# exit code value for die()
    die( "    Stop.\n" );
}


# Carp Error message.
#    Prefix message with the calling function name.
#    Append file and line number where calling function was called.
#    Calling function is the function that called this carp_Error().
#    Intended for user interface functions in a user data file.
#    Only works for first level calls, does not search the call stack.
# call:
#    $self->carp_Error( @text )
#    @text  = error message text
# return:
#    ()  = unused
#
sub carp_Error
{
    my $self = shift();

    my( $package, $file, $line, $subname ) = caller( 1 );
#    print( "carp_Error:  $package  $subname() at ($file line $line)\n" );

    $subname =~ s/.*::// ;		# remove package:: name prefix

    if ( $_ClassData->{TESTMODE} ) {
	$line = 0;		# squash line number to help testing
    }

    $self->Error( "$subname():  ", @_, "    at ($file line $line)\n" );

    1;
}


1;
__END__

