use 5.16.0;
use strict;
use warnings;
use Data::Dumper;

{
	package A;

	sub new{
		my ($class, %attr) = @_;

		$attr{b} = 100;

		return bless \%attr, $class;
	}

	sub get_a{
		my ($self) = @_;

		return $self->{a};
	}
}

{
	package B;

	use base 'A';

	sub get_b{
		my $self = shift;

		return $self->{b};
	}

	sub get{
		my ($self, $field) = @_;

		# say 'field = ' , $field;

		my $ret = sub{
			# say 'field 2= ' , $field;

			# PUBLIC
			if($field eq 'a'){
				return $self->{$field};
				
			# 	print 'a';
			
			# 	print Dumper $self;
				
			# 	return $self->a;
			}

			# PRIVATE
			return 'private';
		};

		return $ret->($field);
	}
}

say '-' x 30;
say "CLASS A:";
my $a = A->new('a' => 12);
print Dumper $a;
say '-' x 30, "\n";
# say $a->{a};
# say $a->get_a;
# say $a->get_a();

say '-' x 30;
say "CLASS B:";
my $b = B->new('a' => 500);
print Dumper $b;
say $b->get('a');
say $b->get('b');
say '-' x 30, "\n";
