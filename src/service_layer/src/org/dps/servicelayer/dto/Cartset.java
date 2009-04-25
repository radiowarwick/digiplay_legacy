package org.dps.servicelayer.dto;

import java.util.List;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.OneToMany;
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
	
	@OneToMany
	@JoinColumn(name="cartset_id")
	@Sort(type = SortType.COMPARATOR, comparator = CartwallPageComparator.class)
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

	public String toString() {
		return name;
	}
}
