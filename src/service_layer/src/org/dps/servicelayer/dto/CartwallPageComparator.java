package org.dps.servicelayer.dto;

import java.util.Comparator;

public class CartwallPageComparator implements Comparator<Cartwall> {

	@Override
	public int compare(Cartwall a, Cartwall b) {
		if(a == null && b == null) {
			return 0;
		}
		if(a == null) {
			return -1;
		}
		if(b == null) {
			return 1;
		}
		if(a.getPage() == null && b.getPage() == null) {
			return 0;
		}
		if(a.getPage() == null) {
			return -1;
		}
		if(b.getPage() == null) {
			return 1;
		}
		return a.getPage().compareTo(b.getPage());
	}

}
