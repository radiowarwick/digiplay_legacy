package org.dps.servicelayer.dto;

import java.util.LinkedList;
import java.util.List;

import javax.persistence.CascadeType;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.OneToMany;
import javax.persistence.OrderBy;
import javax.persistence.PrimaryKeyJoinColumn;
import javax.persistence.Table;

import org.hibernate.annotations.Sort;
import org.hibernate.annotations.SortType;

@Entity
@Table(name="cartset")
@PrimaryKeyJoinColumn(name="file_id")
public class Cartset extends File  {
	
	@Column(name="name")
	private String name;
	
	@Column(name="description")
	private String description;
	
	@OneToMany //TODO: explicit saves or cascade(cascade=CascadeType.ALL)
	@JoinColumn(name="cartset_id", nullable=false)
	@OrderBy("page")
	private List<Cartwall> cartwalls;

	public String getName() {
		return name;
	}

	public void setName(String name_) {
		name = name_;
	}

	public String getDescription() {
		return description;
	}

	public void setDescription(String description_) {
		description = description_;
	}

	public List<Cartwall> getCartwalls() {
		return cartwalls;
	}
	public Cartwall getCartwall(Integer page) {
		Cartwall out = null;
		for(Cartwall wall : cartwalls) {
			if(page.equals(wall.getPage())) {
				out = wall;
				continue;
			}
		}
		return out;
	}
	public void addCartwall(Cartwall cartwall) {
		cartwall.setCartset(this);
		cartwalls.add(cartwall);
	}
	public Cartwall removeCartwall(Cartwall cartwall) {
		Cartwall out = null;
		for(Cartwall wall : cartwalls) {
			if(wall.equals(cartwall)) {
				out = wall;
				continue;
			}
		}
		if(out != null) {
			cartwalls.remove(out);
		}
		return out;
	}
	public Cartwall removeCartwall(Integer page) {
		Cartwall out = null;
		for(Cartwall wall : cartwalls) {
			if(page.equals(wall.getPage())) {
				out = wall;
				continue;
			}
		}
		if(out != null) {
			cartwalls.remove(out);
		}
		return out;
	}

	public String toString() {
		return name;
	}
}
