#!/usr/bin/perl -w
use strict;

# test system, as per https://www.gnu.org/software/automake/manual/html_node/Scripts_002dbased-Testsuites.html#Scripts_002dbased-Testsuites

# tests to compare output of jprefix with expected output
my @tests = (
     # "test name",          "TEST COMMAND",                          CMP,       "EXPECTED OUTPUT"
     #                                                          (eq, =~, or FAIL)
    [ "simple prefix",       "echo x | ./jprefix --text y",              "eq",    "y x" ],
    [ "option processing",   "echo x | ./jprefix --text=y",              "eq",    "y x" ],
    [ "simple suffix",       "echo x | ./jprefix --text=y --suffix",     "eq",    "x y" ],
    [ "prefix empty str",    "echo x | ./jprefix --text ''",             "eq",    "x" ],    # edge case
    [ "prefix space char",   "echo x | ./jprefix --text ' '",            "eq",    "  x" ],  # edge case
    [ "hostname",            "echo x | ./jprefix --text y --hostname",   "=~",    '^y \S+ x$' ],
    [ "timestamp",           "echo x | ./jprefix --text y --timestamp",  "=~",    '^y \S+ \S+ x$' ],
    [ "utimestamp",          "echo x | ./jprefix --text y --utimestamp", "=~",    '^y \S+ \S+ x$' ],

    [ "short options",       "echo A | ./jprefix -s -t B -u",            '=~',    '^A B \S+ \S+$' ],
    [ "long options",        "echo A | ./jprefix --suffix --text B --utime",'=~', '^A B \S+ \S+$' ],

    [ "just quote",          "echo B | ./jprefix --quotes",              "eq",    '"B"' ],
    [ "quote and prefix",    "echo B | ./jprefix --quotes --text A",     "eq",    'A "B"' ],
    [ "quote and suffix",    "echo B | ./jprefix --quotes --text A --suffix", "eq", '"B" A' ],

    [ "read named file",     "./jprefix test/test-file.txt | head -1",            'eq',    '# jprefix' ],
    [ "prefix from file",    "./jprefix --text y test/test-file.txt | head -1",   'eq',    'y # jprefix' ],

    [ "verbose summary",      "echo 'a' | ./jprefix -v | tail -1",        '=~',    ' 2 bytes' ],

    [ "bad option",           "./jprefix --nonopt 2> /dev/null",         'FAIL',  '-'],
);

print "1.." . scalar(@tests) . "\n";    # TAP header

my @results = ();
my $test_num = 0;
for my $test (@tests) {
    $test_num++;
    my $ok;
    my ($name, $cmd, $cmp, $expected) = @$test;
    chomp( my $out = `$cmd` );
    #my $desc = shorten_string( $cmd, 30 );
    my $desc = $cmd;
    #sub show {  # closure, has all params
    #    printf( "%s: $test_num (exit code expected, got exit code '$?') # %s\n", $ok ? "ok" : "not ok", $desc );
    #}
    if ($cmp eq "FAIL") {
        $ok = ($? || $!) ? 1 : 0;
        printf( "%s: $test_num $name (exit code expected, got exit code '$?') # %s\n", $ok ? "ok" : "not ok", $desc );
    } else {
        eval "\$ok = \$out $cmp \$expected";
        printf( "%s: $test_num $name ('$out' $cmp '$expected') # '%s' \n", $ok ? "ok" : "not ok", $desc );
    }
    push(@results, $ok);
}
my @fails = grep { !$_ } @results;

exit( scalar(@fails) ? 1 : 0 );

sub shorten_string {
    my ($str, $max) = @_;
    $max ||= 30;
    if (length($str) > $max) {
        $str = substr( $str, 0, $max-3 ) . "...";
    }
    return $str;
}
