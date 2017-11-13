#!/usr/bin/perl -w
# 2017-08-28  William A. Hudson

# Top-level Stream data into an image.
#
# This object manages the overall display with PerlTk.
# A sub-object, possibly polymorphic, manages the actual input data stream
# transformation into pixel values.
#
#---------------------------------------------------------------------------

package ImTop;

use Tk;			# PerlTk graphics

use strict;

use Error_mixi (	# Error handling functions, mix-in
    'Error',
    'die_Error',
    'carp_Error',
);
# Use mix-in when you want error flag per object.
# Use base class when you only want top-level error flag.


#---------------------------------------------------------------------------
## Main object structure:  (private)
#---------------------------------------------------------------------------
#
# Top Object data:  {SwTop}
# {
#    Error_sub    => sub {},	# Error message reporting subroutine.
#    Error_cnt    => 0,		# Number of errors reported.
#
#    CoeffHeads   => [head,..],	# Coefficient headings for image names.
#
#    Nx           => 0,		# Image N pixels wide.
#    Ny           => 0,		# Image N pixels high.
# }


#---------------------------------------------------------------------------
## Constructor
#---------------------------------------------------------------------------

# Construct a new object and set its attributes.  (public)
#    Required parameters must have a defined value.
#    Optional parameters have default values, and may explicitly be set
#    to undef (e.g. Key => undef).
# call:
#    Package->new( key=> value, ..	# class method call only
#			    # required:
#			    # optional:
#    Error_sub    => sub {},	# Reference to error subroutine.
#    )
# The Error_sub should print error message with appropriate prefix, e.g.:
#        Error_sub    => sub { warn( "Error:  ", @_ ) },
# return:
#    () = new object, undef on error
#
sub new
{
    my( $package, %arg ) = @_;

    my $self = {
		# required args
		# optional args, default values
	Error_sub    => sub { warn( "Error:  ", @_ ) },
		# initialize
	Error_cnt    => 0,
	CoeffHeads   => [],
	Nx           => undef,
	Ny           => undef,
    };

    bless( $self, $package );

    if ( defined( $arg{Error_sub} ) ) {
	if ( ref( $arg{Error_sub} ) eq "CODE" ) {
	    $self->{Error_sub} = delete( $arg{Error_sub} );
	}
	else {
	    $self->Error( "$package->new() 'Error_sub' is not a CODE reference\n" );
	    return( undef );
	}
    }

    # optional args, allow undef values
#    foreach my $key (
#	'',
#    ) {
#	if (                exists( $arg{$key} ) ) {
#	    $self->{$key} = delete( $arg{$key} );
#	}
#    }

    # required args, must be defined values
#    foreach my $key (
#    ) {
#	unless ( defined( $self->{$key} ) ) {
#	    $self->Error( "$package->new() required argument:  '$key'\n" );
#	}
#    }

    foreach my $key ( keys( %arg ) )
    {
	$self->Error( "$package->new() unexpected argument:  '$key'\n" );
    }

    if ( $self->Error() ) {
	return( undef );
    }

    return( $self );
}


# Initialize the object.
# call:
#    $self->Init_required( key=> value, ..
#			    # required:
#    Nx           => 0,		# Image N pixels wide.
#    Ny           => 0,		# Image N pixels high.
#			    # optional:
#    )
# return:
#    () = status, true= ok, false= errors
#
sub Init_required
{
    my( $self, %arg ) = @_;
    my $ok = 1;

    # required args, must be defined values
    foreach my $key (
	'Nx',
	'Ny',
    ) {
	if ( defined( $arg{$key} ) ) {
	    $self->{$key} = delete( $arg{$key} );
	}
	else {
	    $self->Error( "init() required argument:  '$key'\n" );
	    $ok = 0;
	}
    }

    foreach my $key ( keys( %arg ) )
    {
	$self->Error( "Init_required() unexpected argument:  '$key'\n" );
	$ok = 0;
    }

    return( $ok );
}


# Init object attributes.
#    Key must already exist and be undefined.
# call:
#    $self->Init_attrib( KEY=>VALUE, .. )
# return:
#    ()  = unused
#
sub Init_attrib
{
    my( $self, @args ) = @_;

    while ( @args )
    {
	my $key   = shift( @args );
	my $value = shift( @args );

	if ( exists( $self->{$key} ) ) {
	    $self->{$key} = $value;
	}
	else {
	    $self->Error( "init_attrib():  invalid key:  $key\n" );
	}
    }
    1;
}


#---------------------------------------------------------------------------
## Main Window
#---------------------------------------------------------------------------

# Launch the data flow into an image window.
# Create the window.
# call:
#    $self->go_flow(
#        {SX},		# ImStream object
#    )
# return:
#    ()  = unused
#
sub go_flow
{
    my( $self, $sx ) = @_;

    my $save_base = "xx";

    Tk::CmdLine::SetArguments( qw(-geometry +0+0 ) );

    my $mw = MainWindow->new();

    # Use a Frame to group buttons independent of photos.
    my $bframe = $mw->Frame();
    $bframe->pack();

    my $lab1 = $bframe->Label(
	-text => "simage:  Nx= $self->{Nx}, Ny= $self->{Ny}\n" .
		join( ', ', @{$self->{CoeffHeads}} )
    );
    $lab1->pack( -side => 'left' );

    my $but1 = $bframe->Button(
	-text    => 'Quit',
	-command => sub { exit },
    );
    $but1->pack( -side => 'left' );


#    my $im1 = $mw->Photo( 'earth',
#	-file => "/usr/lib/perl5/Tk/demos/images/earth.gif"
#	#-file => "/usr/lib/perl5/Tk/demos/images/teapot.ppm"
#    );
#    my $lab2 = $mw->Label( -image => 'earth' );
#    $lab2->pack();

    unless ( @{$self->{CoeffHeads}} ) {
	$self->Error( "internal:  go_flow() no CoeffHeads\n" )
    }

    my @im_list = ();
    foreach my $head ( @{$self->{CoeffHeads}} )
    {
	my $im_name = "Im_$head";
	my $im2 = $mw->Photo( $im_name,		# make empty photo
	    -width  => $self->{Nx},
	    -height => $self->{Ny},
	);
	my $lab2 = $mw->Label( -image => $im_name,
	    -relief => 'solid',
	);
	$lab2->pack( -side => 'left' );

	# mark corners of image
	my $nx = $self->{Nx};
	my $ny = $self->{Ny};
	$im2->put( "#cf00ff", -to =>     0,    0,   4,4   );
	$im2->put( "#cf00ff", -to => $nx-4,    0, $nx,4   );
	$im2->put( "#cf00ff", -to =>     0,$ny-4,   4,$ny );
	$im2->put( "#cf00ff", -to => $nx-4,$ny-4, $nx,$ny );

	push( @im_list, $im2 );
	print( "simage:  im_name= $im_name\n" );
    }

    $sx->Init_attrib( ImPhotos => \@im_list );

    print( "simage:  Nx= $self->{Nx}, Ny= $self->{Ny}\n" );

    my $lab3 = $bframe->Label(
	-text => "    ${save_base}.*.ppm",
    );
    $lab3->pack( -side => 'left' );

    my $but3 = $bframe->Button(
	-text    => "Save",
	-command => sub {
	    my $ii = 0;
	    foreach my $im ( @im_list )
	    {
		my $head = $self->{CoeffHeads}->[$ii++];
		my $save_file = "${save_base}.${head}.ppm";
		print( "Save:  $save_file\n" );
		$im->write(  $save_file,
		    -format => "ppm",
		);
	    }
	},
    );
    $but3->pack( -side => 'left' );


    # start streaming data
    $sx->{AfterID} = $mw->repeat( 10,	# milliseconds
	sub{ $sx->stream_pixels() || $sx->{AfterID}->cancel() }
    );
    # see:  Tk::after(3pm)  has repeat()

    MainLoop();
    # Window is not shown until now.
    # Returns when last window is destroyed.

    1;
}


#---------------------------------------------------------------------------
## Debug
#---------------------------------------------------------------------------

# Get object attributes as text.
# call:
#    $self->text_attrib( KEY,.. )
# return:
#    ()  = @text
#
sub text_attrib
{
    my( $self, @keys ) = @_;

    my @text;
    foreach my $key ( @keys )
    {
	my $value = $self->{$key};
	unless ( defined( $value ) ) {
	    $value = 'undef';
	}
	my $text = sprintf( "%-12s => %s,\n", $key, $value );
	push( @text, $text );
    }

    return( @text );
}


# Get object attributes as a multiline string.
#    Intended only for Testing.
# call:
#    $self->str_attrib( KEY,.. )
# return:
#    ()  = @text
#
sub str_attrib
{
    my( $self, @keys ) = @_;

    return( join( "", $self->text_attrib( @keys ) ) );
#    return( join( "\t", "\n", $self->text_attrib( @keys ) ) );
}


#---------------------------------------------------------------------------
## Accessors
#---------------------------------------------------------------------------


1;
__END__

