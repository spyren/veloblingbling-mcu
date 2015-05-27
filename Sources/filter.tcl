#!/bin/sh
#\
exec tclsh "$0" "$@"

while { [gets stdin line] >= 0} {
    if { [string match \{* $line] } {
	set start_array [string first \{ $line] 
        set end_array   [string first \} $line]
	set rest [string range $line $end_array [string length $line]]
	incr start_array
        incr end_array -1
	set array [string range $line $start_array $end_array]
	set array_l [split $array ,]
	puts -nonewline \{
	for {set i 0} {$i < [llength $array_l]} {incr i 2} {
	    puts -nonewline [lindex $array_l [expr $i+1]]
	    puts -nonewline [string range [lindex $array_l $i] 2 4]
	    if {$i < [expr [llength $array_l] - 2]} {
		puts -nonewline ", "
	    }
	}
	
	puts $rest
    } else { 
	puts $line
    }
}
